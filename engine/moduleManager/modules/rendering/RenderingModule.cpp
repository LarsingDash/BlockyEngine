//
// Created by 11896 on 15/11/2024.
//

#include "RenderingModule.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

RenderingModule::RenderingModule(SDL_Renderer* renderer) : renderer(renderer) {}

RenderingModule::~RenderingModule() = default;

void RenderingModule::Render(const std::vector<std::reference_wrapper<Renderable>>& renderables) {
	for (Renderable& renderable : renderables) {
		switch (renderable.GetRenderableType()) {
			case RECTANGLE:
				RenderRectangle(reinterpret_cast<RectangleRenderable&>(renderable));
				break;
			case ELLIPSE:
				RenderEllipse(reinterpret_cast<EllipseRenderable&>(renderable));
				break;
			case SPRITE:
				RenderSprite(reinterpret_cast<SpriteRenderable&>(renderable));
				break;
		}
	}
}

void RenderingModule::RenderRectangle(RectangleRenderable& renderable) {
	glm::ivec4 color = renderable.GetColor();
	ComponentTransform& transform = *renderable.componentTransform;

	//Precalculating rotation angle
	float rad = transform.GetWorldRotation() * static_cast<float>(M_PI) / 180.f;
	float cosTheta = cos(rad);
	float sinTheta = sin(rad);

	//Pre-getting dimensions
	const auto& position = transform.GetWorldPosition();
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
		filledPolygonRGBA(renderer, xPoints, yPoints, 4,
						  color.r, color.g, color.b, color.a);
	} else {
		polygonRGBA(renderer, xPoints, yPoints, 4,
					color.r, color.g, color.b, color.a);
	}
}

void RenderingModule::RenderEllipse(EllipseRenderable& renderable) {
	glm::ivec4 color = renderable.GetColor();

	ComponentTransform& transform = *renderable.componentTransform;
	const auto& position = transform.GetWorldPosition();
	const auto& scale = transform.GetWorldScale();

	auto centerX = static_cast<Sint16>(position.x);
	auto centerY = static_cast<Sint16>(position.y);
	auto radiusX = static_cast<Sint16>(scale.x / 2.0f);
	auto radiusY = static_cast<Sint16>(scale.y / 2.0f);

	if (renderable.IsFilled()) {
		filledEllipseRGBA(renderer, centerX, centerY, radiusX, radiusY,
						  color.r, color.g, color.b, color.a);
	} else {
		ellipseRGBA(renderer, centerX, centerY, radiusX, radiusY,
					color.r, color.g, color.b, color.a);
	}
}

void RenderingModule::RenderSprite(SpriteRenderable& renderable) {
	int width, height;
	SDL_Texture* texture = LoadTexture(renderable, width, height);
	if (!texture) {
		return;
	}

	RenderTexture(texture, *renderable.componentTransform);
}

SDL_Texture* RenderingModule::LoadTexture(const SpriteRenderable& sprite, int& width, int& height) {
	const std::string& spriteTag = sprite.GetSpriteTag();

	//Check if the texture is already cached
	auto it = textureCache.find(spriteTag);
	if (it != textureCache.end()) {
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
		std::cerr << "Failed to load image: " << filePath << std::endl;
		return nullptr;
	}

	//Create an SDL surface
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
			imageData, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32
	);
	if (!surface) {
		std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
		stbi_image_free(imageData);
		return nullptr;
	}

	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> texture(
			SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture
	);

	SDL_FreeSurface(surface);
	stbi_image_free(imageData);

	if (!texture) {
		std::cerr << "Failed to create SDL texture: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	auto result = textureCache.emplace(spriteTag, std::move(texture));

	//Return texture address if the emplacement was successful (result.second == true)
	return result.second ? result.first->second.get() : nullptr;
}

void RenderingModule::RenderTexture(SDL_Texture* texture, const ComponentTransform& transform) {
	if (!texture) {
		std::cerr << "Cannot render null texture." << std::endl;
		return;
	}

	const auto& position = transform.GetWorldPosition();
	const auto& scale = transform.GetWorldScale();
	SDL_FRect destRect = {
			(position.x - scale.x / 2.0f),
			(position.y - scale.y / 2.0f),
			scale.x,
			scale.y
	};
	SDL_RenderCopyExF(
			renderer, texture, nullptr, &destRect,
			transform.GetWorldRotation(), nullptr, SDL_RendererFlip::SDL_FLIP_NONE
	);
}

