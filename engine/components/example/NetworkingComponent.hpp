//
// Created by 11896 on 11/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_NETWORKINGCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_NETWORKINGCOMPONENT_HPP_

#include "components/Component.hpp"
#include "moduleManager/modules/networking/NetworkingModule.hpp"
#include "moduleManager/modules/WindowModule.hpp"

class NetworkingComponent : public Component {
	public:
		NetworkingComponent(GameObject* gameObject, const char* tag);
		~NetworkingComponent() override;

		void Start() override;
		void Update(float delta) override;
		void End() override;
		static std::string GetTimestamp();

	private:
		void _renderNetworkingGUI();

		ImGuiRenderingModule& _imguiModule;
		NetworkingModule& _networkingModule;
		ImGuiTextBuffer _logBuffer;

		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_NETWORKINGCOMPONENT_HPP_
