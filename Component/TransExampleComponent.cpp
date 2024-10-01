//
// Created by larsv on 01/10/2024.
//

#include "TransExampleComponent.hpp"
#include "../renderer.cpp"
#include "trigonometric.hpp"

TransExampleComponent::TransExampleComponent(GameObject& gameObject, Transform& transform)
		: Component(gameObject, transform) {
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0, 150, 0));

	texture = SDL_CreateTextureFromSurface(Example::renderer, surface);
	SDL_FreeSurface(surface);

	rect = new SDL_FRect();
}

void TransExampleComponent::OnUpdate(float delta) {
	const glm::vec2& pos = transform.GetWorldPosition();
	rect->x = pos.x;
	rect->y = pos.y;

	const glm::vec2& scale = transform.GetWorldScale();
	rect->w = scale.x;
	rect->h = scale.y;
	
	SDL_RenderCopyExF(Example::renderer, texture, nullptr, rect,
					  glm::degrees(transform.GetWorldRotation()), nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

TransExampleComponent::~TransExampleComponent() {
	delete rect;
	SDL_DestroyTexture(texture);
}

