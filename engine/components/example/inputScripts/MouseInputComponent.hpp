#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_

#include "gameObject/GameObject.hpp"
#include "moduleManager/modules/input/MouseInput.hpp"
#include "moduleManager/modules/input/MouseEvent.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "moduleManager/modules/input/InputModule.hpp"
#include "moduleManager/modules/rendering/RenderingModule.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

class MouseInputComponent : public Component {
	public:
		MouseInputComponent(GameObject* parent, const char* tag);

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void PaletteGUI();
		void SoundGUI();

	private:
		Component* _clone(const GameObject& parent) override;

		void HandleMouseInput(MouseButtonState state, int x, int y, const glm::vec4& color);

		InputModule& _inputModule;
		Camera& _camera;
		ImGuiRenderingModule& _imguiModule;

		int currentPalette = 0;
		glm::vec4 colorPalettes[3][3] = {
			{
				glm::vec4(255.f, 0.f, 0.f, 255.f),
				glm::vec4(0.f, 0.f, 255.f, 255.f),
				glm::vec4(0.f, 255.f, 0.f, 255.f)
			},

			{
				glm::vec4(128.f, 50.f, 0.f, 255.f),
				glm::vec4(50.f, 128.f, 0.f, 255.f),
				glm::vec4(0.f, 50.f, 128.f, 255.f)
			},

			{
				glm::vec4(255.f, 255.f, 0.f, 255.f),
				glm::vec4(0.f, 255.f, 255.f, 255.f),
				glm::vec4(255.f, 0.f, 255.f, 255.f)
			}
		};

		float _mainMusicVolume = 0.5f; // Default volume level
		float _soundEffectsVolume = 0.5f; // Default volume level
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_CUSTOM_MOUSEINPUTCOMPONENT_HPP_
