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
			case RECTANGLE:RenderRectangle(reinterpret_cast<RectangleRenderable&>(renderable));
				break;
			case ELLIPSE:RenderEllipse(reinterpret_cast<EllipseRenderable&>(renderable));
				break;
			case SPRITE:RenderSprite(reinterpret_cast<SpriteRenderable&>(renderable));
				break;
		}
	}
}

void RenderingModule::RenderRectangle(RectangleRenderable& renderable) {
	glm::ivec4 color = renderable.GetColor();
	ComponentTransform& transform = *renderable.componentTransform;

	float rad = transform.rotation * static_cast<float>(M_PI) / 180.f;
	float cosTheta = cos(rad);
	float sinTheta = sin(rad);

	int x = static_cast<int>(std::round(transform.position.x));
	int y = static_cast<int>(std::round(transform.position.y));
	int w = static_cast<int>(std::round(transform.scale.x));
	int h = static_cast<int>(std::round(transform.scale.y));

	SDL_Point points[4];
	points[0] = {x + static_cast<int>(-w / 2 * cosTheta - -h / 2 * sinTheta), y + static_cast<int>(-w / 2 * sinTheta + -h / 2 * cosTheta)};
	points[1] = {x + static_cast<int>(w / 2 * cosTheta - -h / 2 * sinTheta), y + static_cast<int>(w / 2 * sinTheta + -h / 2 * cosTheta)};
	points[2] = {x + static_cast<int>(w / 2 * cosTheta - h / 2 * sinTheta), y + static_cast<int>(w / 2 * sinTheta + h / 2 * cosTheta)};
	points[3] = {x + static_cast<int>(-w / 2 * cosTheta - h / 2 * sinTheta), y + static_cast<int>(-w / 2 * sinTheta + h / 2 * cosTheta)};

	Sint16 xPoints[4], yPoints[4];
	for (int i = 0; i < 4; ++i) {
		xPoints[i] = static_cast<Sint16>(points[i].x);
		yPoints[i] = static_cast<Sint16>(points[i].y);
	}

	if (renderable.IsFilled()) filledPolygonRGBA(renderer, xPoints, yPoints, 4, color.r, color.g, color.b, color.a);
	else polygonRGBA(renderer, xPoints, yPoints, 4, color.r, color.g, color.b, color.a);
}

void RenderingModule::RenderEllipse(EllipseRenderable& renderable) {
	glm::ivec4 color = renderable.GetColor();

	ComponentTransform& transform = *renderable.componentTransform;

	auto centerX = static_cast<Sint16>(transform.position.x);
	auto centerY = static_cast<Sint16>(transform.position.y);
	auto radiusX = static_cast<Sint16>(transform.scale.x / 2.0f);
	auto radiusY = static_cast<Sint16>(transform.scale.y / 2.0f);

	if (renderable.IsFilled()) filledEllipseRGBA(renderer, centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);
	else ellipseRGBA(renderer, centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);
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

	// Check if the texture is already cached
	auto it = textureCache.find(spriteTag);
	if (it != textureCache.end()) {
		SDL_QueryTexture(it->second.get(), nullptr, nullptr, &width, &height);
		return it->second.get();
	}

	//Load image using stb_image
	const std::string& filePath = sprite.GetFilePath();
	int channels;
	unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	if (!imageData) {
		std::cerr << "Failed to load image: " << filePath << std::endl;
		return nullptr;
	}

	// Create an SDL surface
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(imageData, width, height, 32, width * 4,
															  SDL_PIXELFORMAT_RGBA32);
	if (!surface) {
		std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
		stbi_image_free(imageData);
		return nullptr;
	}

	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>
			texture(SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture);

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

	SDL_FRect destRect = {
			(transform.position.x - transform.scale.x / 2.0f),
			(transform.position.y - transform.scale.y / 2.0f),
			transform.scale.x,
			transform.scale.y
	};

	SDL_RenderCopyExF(renderer, texture, nullptr, &destRect, transform.rotation, nullptr,
					  SDL_RendererFlip::SDL_FLIP_NONE);
}

