//
// Created by 11896 on 11/12/2024.
//

#include <cstring>
#include "NetworkingComponent.hpp"
#include "moduleManager/ModuleManager.hpp"

NetworkingComponent::NetworkingComponent(GameObject* gameObject, const char* tag)
		: Component(gameObject, tag),
		  networkingModule(ModuleManager::GetInstance().GetModule<NetworkingModule>()),
		  imguiModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetGuiRenderingModule()) {}

NetworkingComponent::~NetworkingComponent() = default;

Component* NetworkingComponent::_clone(const GameObject& parent) {
	return new NetworkingComponent(*this);
}

void NetworkingComponent::Start() {
	imguiModule.AddComponent("Networking", [this]() {
		RenderNetworkingGUI();
	});
}

void NetworkingComponent::Update(float delta) {
	networkingModule.Update(delta);
}

void NetworkingComponent::End() {}

void NetworkingComponent::RenderNetworkingGUI() {
	ImGui::Begin("Networking Test");

	static char host[128] = "127.0.0.1";
	static int port = 12345;
	static char message[512] = "";

	if (ImGui::Button("Host")) {
		networkingModule.Host(port);
	}

	ImGui::InputText("Host Address", host, sizeof(host));
	ImGui::InputInt("Port", &port);
	if (ImGui::Button("Join")) {
		networkingModule.Join(host, port);
	}

	ImGui::InputText("Message", message, sizeof(message));
	if (ImGui::Button("Send")) {
		networkingModule.SendMessage(message);
	}

	ImGui::End();
}




