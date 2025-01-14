//
// Created by larsv on 14/01/2025.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_MOVE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_MOVE_HPP_

#include <components/Component.hpp>
#include "moduleManager/modules/input/KeyInput.hpp"

class Move : public Component {
	public:
		Move(GameObject* gameObject, const char* tag, KeyInput up, KeyInput down);
		~Move() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;
		
	private:
		KeyInput _up;
		KeyInput _down;

		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_MOVE_HPP_
