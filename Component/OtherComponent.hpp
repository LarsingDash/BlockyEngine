//
// Created by larsv on 25/09/2024.
//

#ifndef BLOCKYENGINE_OTHERCOMPONENT_HPP
#define BLOCKYENGINE_OTHERCOMPONENT_HPP

#include "Component.hpp"
#include "Transform.hpp"
#include "../GameObject/GameObject.hpp"
#include "SDL_rect.h"

class OtherComponent : public Component {
	public:
		OtherComponent(GameObject& gameObject, Transform& transform, int x, int y, int greyScale);

		OtherComponent(GameObject& gameObject, Transform& transform)
				: OtherComponent(gameObject, transform, 0, 0, 0) {};

		void OnUpdate(float delta) override;
		~OtherComponent() override;
	private:
		SDL_Rect* rect;
		int greyScale;
		float counter{};
};


#endif //BLOCKYENGINE_OTHERCOMPONENT_HPP
