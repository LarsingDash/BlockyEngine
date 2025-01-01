//
// Created by larsv on 10/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_MOUSECAMERACONTROLLER_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_MOUSECAMERACONTROLLER_HPP_

#include "components/Component.hpp"
#include "moduleManager/modules/input/InputModule.hpp"
#include "moduleManager/modules/rendering/Camera.hpp"
#include "utilities/JsonUtil.hpp"

class MouseCameraController : public Component {
	public:
		MouseCameraController(GameObject* gameObject, const char* tag);
		~MouseCameraController() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;

		JSON_REGISTER_HEADER_DEFAULTS(MouseCameraController);

	private:
		Component* _clone(const GameObject& parent) override;

		glm::vec2 _threshold;
		glm::vec2 _middle;

		Camera& _camera;
		InputModule& _inputModule;
};

JSON_REGISTER_COMPONENT(MouseCameraController);

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_MOUSECAMERACONTROLLER_HPP_
