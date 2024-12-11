//
// Created by 11896 on 15/11/2024.
//

#include "RenderingModule.hpp"
#include "SDL_render.h"
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"

#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "components/renderables/AnimationRenderable.hpp"
#include "logging/BLogger.hpp"
#include "utilities/TimeUtil.hpp"

RenderingModule::RenderingModule(SDL_Renderer* renderer) :
		_renderer(renderer), _camera(std::make_unique<Camera>()) {
	_font = TTF_OpenFont("../assets/fonts/font1.ttf", 24);
	if (!_font) {
		std::string err("Failed to load font: ");
		err += TTF_GetError();
		BLOCKY_ENGINE_ERROR(err)
	}
}

RenderingModule::~RenderingModule() = default;

void RenderingModule::Render() {
	for (const auto& [layer, list] : _renderables) {
		for (Renderable& renderable : list) {
			switch (renderable.GetRenderableType()) {
				case RECTANGLE:
					_renderRectangle(reinterpret_cast<RectangleRenderable&>(renderable));
					break;
				case ELLIPSE:
					_renderEllipse(reinterpret_cast<EllipseRenderable&>(renderable));
					break;
				case SPRITE:
					_renderSprite(reinterpret_cast<SpriteRenderable&>(renderable));
					break;
				case ANIMATED:
					_renderAnimatedSprite(reinterpret_cast<AnimationRenderable&>(renderable));
					break;
				case TEXT:
					_renderText(reinterpret_cast<TextRenderable&>(renderable));
					break;
			}
		}
	}

	if (TimeUtil::GetInstance().IsFpsCounterEnabled()) {
		_renderFps();
	}
}

void RenderingModule::_renderRectangle(RectangleRenderable& renderable) {
	glm::ivec4 color = renderable.GetColor();
	ComponentTransform& transform = *renderable.componentTransform;

	//Precalculating rotation angle
	float rad = transform.GetWorldRotation() * static_cast<float>(M_PI) / 180.f;
	float cosTheta = cos(rad);
	float sinTheta = sin(rad);

	//Pre-getting dimensions
	const auto& position = transform.GetWorldPosition() - _camera->GetPosition();
	const auto& scale = transform.GetWorldScale();
	float x = position.x;
	float y = position.y;
	float w = scale.x / 2.f;
	float h = scale.y / 2.f;

	//Precalculating rotated dimensions
	float cosW = w * cosTheta;
	float sinW = w * sinTheta;
	float cosH = h * cosTheta;
	float sinH = h * sinTheta;

	//Precalculating points on polygon
	SDL_Point points[4] = {
			{static_cast<int>(x + std::round(-cosW - -sinH)), static_cast<int>(y + std::round(-sinW + -cosH))},
			{static_cast<int>(x + std::round(cosW - -sinH)), static_cast<int>(y + std::round(sinW + -cosH))},
			{static_cast<int>(x + std::round(cosW - sinH)), static_cast<int>(y + std::round(sinW + cosH))},
			{static_cast<int>(x + std::round(-cosW - sinH)), static_cast<int>(y + std::round(-sinW + cosH))}
	};

	//Transforming SDL_Points[] to Sint16[]
	Sint16 xPoints[4], yPoints[4];
	for (int i = 0; i < 4; ++i) {
		xPoints[i] = static_cast<Sint16>(points[i].x);
		yPoints[i] = static_cast<Sint16>(points[i].y);
	}

	//SDL2_gfx (Filled)PolygonRGBA
	if (renderable.IsFilled()) {
		filledPolygonRGBA(_renderer, xPoints, yPoints, 4,
						  color.r, color.g, color.b, color.a);
	} else {
		polygonRGBA(_renderer, xPoints, yPoints, 4,
					color.r, color.g, color.b, color.a);
	}
}

void RenderingModule::_renderEllipse(EllipseRenderable& renderable) {
	glm::ivec4 color = renderable.GetColor();

	ComponentTransform& transform = *renderable.componentTransform;
	const auto& position = transform.GetWorldPosition() - _camera->GetPosition();
	const auto& scale = transform.GetWorldScale();

	auto centerX = static_cast<Sint16>(position.x);
	auto centerY = static_cast<Sint16>(position.y);
	auto radiusX = static_cast<Sint16>(scale.x / 2.0f);
	auto radiusY = static_cast<Sint16>(scale.y / 2.0f);

	if (renderable.IsFilled()) {
		filledEllipseRGBA(_renderer, centerX, centerY, radiusX, radiusY,
						  color.r, color.g, color.b, color.a);
	} else {
		ellipseRGBA(_renderer, centerX, centerY, radiusX, radiusY,
					color.r, color.g, color.b, color.a);
	}
}

void RenderingModule::_renderSprite(SpriteRenderable& renderable) {
	int width, height;
	SDL_Texture* texture = _loadTexture(renderable, width, height);
	if (!texture) {
		return;
	}
	_renderTexture(texture, *renderable.componentTransform, nullptr);
}

void RenderingModule::_renderAnimatedSprite(AnimationRenderable& renderable) {
	int width, height;
	SDL_Texture* texture = _loadTexture(renderable, width, height);
	if (!texture) {
		return;
	}

	const glm::ivec4* sourceRect = renderable.GetSourceRect();

	_renderTexture(texture, *renderable.componentTransform, sourceRect);
}

SDL_Texture* RenderingModule::_loadTexture(const SpriteRenderable& sprite, int& width, int& height) {
	const std::string& spriteTag = sprite.GetSpriteTag();

	//Check if the texture is already cached
	auto it = _textureCache.find(spriteTag);
	if (it != _textureCache.end()) {
		SDL_QueryTexture(it->second.get(), nullptr, nullptr, &width, &height);
		return it->second.get();
	}

	//Load image using stb_image
	const std::string& filePath = sprite.GetFilePath();
	int channels;
	unsigned char* imageData = stbi_load(
			filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha
	);
	if (!imageData) {
		std::string err("Failed to load image: ");
		err += filePath;
		BLOCKY_ENGINE_ERROR(err)
		return nullptr;
	}

	//Create an SDL surface
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
			imageData, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32
	);
	if (!surface) {
		std::string err("Failed to create SDL surface: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err)
		stbi_image_free(imageData);
		return nullptr;
	}

	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> texture(
			SDL_CreateTextureFromSurface(_renderer, surface), SDL_DestroyTexture
	);

	SDL_FreeSurface(surface);
	stbi_image_free(imageData);

	if (!texture) {
		std::string err("Failed to create SDL texture: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err)
		return nullptr;
	}

	auto result = _textureCache.emplace(spriteTag, std::move(texture));

	//Return texture address if the emplacement was successful (result.second == true)
	return result.second ? result.first->second.get() : nullptr;
}

void RenderingModule::_renderTexture(SDL_Texture* texture,
									 const ComponentTransform& transform,
									 const glm::ivec4* sourceRect) {
	if (!texture) {
		BLOCKY_ENGINE_ERROR("Cannot render null texture.")
		return;
	}

	const auto& position = transform.GetWorldPosition() - _camera->GetPosition();
	const auto& scale = transform.GetWorldScale();
	SDL_FRect destRect = {
			position.x - scale.x / 2.0f,
			position.y - scale.y / 2.0f,
			scale.x,
			scale.y
	};

	SDL_Rect sdlSourceRect;
	if (sourceRect) {
		sdlSourceRect = {
				sourceRect->x,
				sourceRect->y,
				sourceRect->z,
				sourceRect->w
		};
	}

	SDL_RenderCopyExF(
			_renderer, texture, sourceRect ? &sdlSourceRect : nullptr, &destRect,
			transform.GetWorldRotation(), nullptr, SDL_RendererFlip::SDL_FLIP_NONE
	);
}
void RenderingModule::_renderText(TextRenderable& renderable) {
	const auto& color = renderable.GetColor();
	SDL_Color sdlColor = {
			static_cast<Uint8>(color.r),
			static_cast<Uint8>(color.g),
			static_cast<Uint8>(color.b),
			static_cast<Uint8>(color.a)
	};

	const auto& position = renderable.componentTransform->GetWorldPosition();
	const std::string& text = renderable.GetText();

	_renderTextHelper(
			text, sdlColor, {position.x, position.y},
			renderable.componentTransform->GetWorldRotation()
	);
}

void RenderingModule::_renderFps() {
	int fps = TimeUtil::GetInstance().GetFPS();

	SDL_Color color;
	if (fps >= 60) {
		color = {0, 255, 0, 255};
	} else if (fps >= 30) {
		color = {255, 255, 0, 255};
	} else {
		color = {255, 0, 0, 255};
	}

	std::string fpsText = "FPS: " + std::to_string(fps);

	int windowWidth, windowHeight;
	SDL_GetRendererOutputSize(_renderer, &windowWidth, &windowHeight);

	int textWidth, textHeight;
	TTF_SizeText(_font, fpsText.c_str(), &textWidth, &textHeight);
	SDL_FPoint position = {static_cast<float>(windowWidth - textWidth - 10), 10};

	_renderTextHelper(fpsText, color, position, 0, false);
}

void RenderingModule::_renderTextHelper(const std::string& text,
										const SDL_Color& color,
										const SDL_FPoint& position,
										float angle,
										bool moveWithCamera) {
	SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), color);
	if (!surface) {
		std::string err("Failed to create text surface: ");
		err += TTF_GetError();
		BLOCKY_ENGINE_ERROR(err)
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::string err("Failed to create text texture: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err)
		return;
	}

	int textWidth, textHeight;
	SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);
	SDL_Rect dstRect;
	if (moveWithCamera)
		dstRect = {
				static_cast<int>(position.x - _camera->GetPosition().x),
				static_cast<int>(position.y - _camera->GetPosition().y),
				textWidth,
				textHeight
		};
	else {
		dstRect = {
				static_cast<int>(position.x),
				static_cast<int>(position.y),
				textWidth,
				textHeight
		};
	}

	SDL_RenderCopyEx(_renderer,
					  texture,
					  nullptr,
					  &dstRect,
					  angle,
					  nullptr,
					  SDL_RendererFlip::SDL_FLIP_NONE
	);
	SDL_DestroyTexture(texture);
}

void RenderingModule::AddRenderable(Renderable& renderable) {
	_renderables[renderable.GetLayer()].emplace_back(renderable);
}

void RenderingModule::RemoveRenderable(Renderable& renderable) {
	try {
		auto& layer = _renderables.at(renderable.GetLayer());
		auto renderableIt = std::find_if(layer.begin(), layer.end(),
										 [&renderable](const std::reference_wrapper<Renderable>& other) {
											 return &renderable == &other.get();
										 });

		if (renderableIt != layer.end()) {
			layer.erase(renderableIt);
		}
	} catch (const std::out_of_range& e) {
		std::string err("Removal of renderable {");
		err += renderable.tag;
		err += "} was requested on layer ";
		err += std::to_string(renderable.GetLayer());
		err += ", but that layer was not found.";
		BLOCKY_ENGINE_ERROR(err)
	}
}
