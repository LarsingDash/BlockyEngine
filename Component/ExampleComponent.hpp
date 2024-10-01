//
// Created by larsv on 24/09/2024.
//

#ifndef BLOCKYENGINE_EXAMPLECOMPONENT_HPP
#define BLOCKYENGINE_EXAMPLECOMPONENT_HPP

#include "Component.hpp"
#include "../GameObject/Transform.hpp"
#include "../GameObject/GameObject.hpp"
#include "SDL_rect.h"

class ExampleComponent : public Component {
	public:
		ExampleComponent(GameObject& gameObject, Transform& transform, int x, int y, int greyScale);

		ExampleComponent(GameObject& gameObject, Transform& transform)
				: ExampleComponent(gameObject, transform, 0, 0, 0) {};

		void OnUpdate(float delta) override;
		~ExampleComponent() override;
	private:
		SDL_Rect* rect;
		int greyScale;
		float counter{};
};

#endif //BLOCKYENGINE_EXAMPLECOMPONENT_HPP
