#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_KEYBOARDINPUTCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_KEYBOARDINPUTCOMPONENT_HPP_

#include "gameObject/GameObject.hpp"
#include "moduleManager/modules/input/KeyEvent.hpp"
#include "moduleManager/modules/input/InputModule.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"
#include "components/animation/AnimationController.hpp"

class KeyboardInputComponent : public Component {
	public:
		KeyboardInputComponent(GameObject& parent, const char* tag, GameObject& animatedObject);

		void Start() override;
		void Update(float delta) override;
		void End() override;

	private:
		void ChangeAnimation(const std::string& animationName);

		InputModule& _inputModule = ModuleManager::getInstance().getModule<WindowModule>().GetInputModule();
		GameObject& _animatedObject;
		AnimationController* _animationController = nullptr;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_KEYBOARDINPUTCOMPONENT_HPP_
