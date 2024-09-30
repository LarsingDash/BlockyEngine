//
// Created by larsv on 24/09/2024.
//

#include <iostream>
#include "ExampleComponent.h"
#include "SDL_render.h"
#include "../renderer.cpp"

ExampleComponent::ExampleComponent(GameObject& gameObject, Transform& transform, int x, int y, int greyScale)
		: Component(gameObject, transform), rect(new SDL_Rect{x, y, 100, 100}) {
	this->greyScale = greyScale;
}

void ExampleComponent::OnUpdate(float delta) {
	SDL_SetRenderDrawColor(Example::renderer, greyScale, greyScale, greyScale, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(Example::renderer, rect);
	
	counter += delta;
	if (counter >= 1) gameObject.RemoveComponent<ExampleComponent>();
}

ExampleComponent::~ExampleComponent() {
	std::cout << "Deleting Example from: " << gameObject.tag << std::endl;
	delete rect;
}
