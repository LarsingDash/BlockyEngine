#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_

#include "moduleManager/modules/input/InputModule.hpp"

class MouseInputComponent : public Component {
	public:
		MouseInputComponent(GameObject* parent, const char* tag);

		void Start() override;
		void Update(float delta) override;
		void End() override;
		
	private:
		Component* _clone(const GameObject& parent) override;
		
		void HandleMouseInput(MouseButtonState state, int x, int y, const glm::vec4& color);

		InputModule& _inputModule;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_
