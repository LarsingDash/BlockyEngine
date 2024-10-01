//
// Created by larsv on 01/10/2024.
//

#ifndef BLOCKYENGINE_TRANSOTHERCOMPONENT_HPP
#define BLOCKYENGINE_TRANSOTHERCOMPONENT_HPP

#include "Component.hpp"
#include "../GameObject/Transform.hpp"
#include "../GameObject/GameObject.hpp"
#include "SDL_render.h"

class TransOtherComponent : public Component {
	public:
		TransOtherComponent(GameObject& gameObject, Transform& transform);
		void OnUpdate(float delta) override;
		~TransOtherComponent() override = default;;
};


#endif //BLOCKYENGINE_TRANSOTHERCOMPONENT_HPP
