#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_KEYBOARDINPUTCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_KEYBOARDINPUTCOMPONENT_HPP_

#include "moduleManager/modules/input/InputModule.hpp"
#include "components/animation/AnimationController.hpp"

class KeyboardInputComponent : public Component {
	public:
		KeyboardInputComponent(GameObject* parent, const char* tag);

		void Start() override;
		void Update(float delta) override;
		void End() override;

		Component* _cloneImpl(GameObject& parent) override;

	private:
		void ChangeAnimation(const std::string& animationName);

		InputModule& _inputModule;
		AnimationController* _animationController = nullptr;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_KEYBOARDINPUTCOMPONENT_HPP_
