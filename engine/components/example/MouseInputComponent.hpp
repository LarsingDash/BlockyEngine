#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_

#include "gameObject/GameObject.hpp"
#include "moduleManager/modules/input/MouseInput.hpp"
#include "moduleManager/modules/input/MouseEvent.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "moduleManager/modules/input/InputModule.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

class MouseInputComponent : public Component {
	public:
		MouseInputComponent(GameObject& parent, const char* tag);

		void Start() override;
		void Update(float delta) override;
		void End() override;

	private:
		void HandleMouseInput(MouseButtonState state, int x, int y, const glm::vec4& color);

		InputModule& _inputModule = ModuleManager::getInstance().getModule<WindowModule>().GetInputModule();
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_
