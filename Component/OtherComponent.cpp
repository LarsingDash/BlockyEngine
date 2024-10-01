﻿//
// Created by larsv on 25/09/2024.
//

#include <iostream>
#include "OtherComponent.hpp"
#include "SDL_render.h"
#include "../renderer.cpp"

OtherComponent::OtherComponent(GameObject& gameObject, Transform& transform, int x, int y, int greyScale)
		: Component(gameObject, transform), rect(new SDL_Rect{x, y, 50, 50}) {
	this->greyScale = greyScale;
}

void OtherComponent::OnUpdate(float delta) {
	SDL_SetRenderDrawColor(Example::renderer, greyScale, greyScale, greyScale, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(Example::renderer, rect);

	counter += delta;
	if (counter >= 2) gameObject.RemoveComponent<OtherComponent>();
}

OtherComponent::~OtherComponent() {
	std::cout << "Deleting Other from: " << gameObject.tag << std::endl;
	delete rect;
}
