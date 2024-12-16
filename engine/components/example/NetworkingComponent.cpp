//
// Created by 11896 on 11/12/2024.
//

#include <iostream>
#include "NetworkingComponent.hpp"
#include "moduleManager/ModuleManager.hpp"

NetworkingComponent::NetworkingComponent(GameObject* gameObject, const char* tag)
		: Component(gameObject, tag),
		  _networkingModule(ModuleManager::GetInstance().GetModule<NetworkingModule>()),
		  _imguiModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetGuiRenderingModule()) {}

NetworkingComponent::~NetworkingComponent() = default;

Component* NetworkingComponent::_clone(const GameObject& parent) {
	return new NetworkingComponent(*this);
}

void NetworkingComponent::Start() {
	_imguiModule.AddComponent("Networking", [this]() {
		_renderNetworkingGUI();
	});

	_networkingModule.AddMessageListener("NetListener1", [this](const std::string& message) {
		_onMessageReceived(message);
	});
}

void NetworkingComponent::Update(float delta) {
}

void NetworkingComponent::End() {
	_networkingModule.RemoveMessageListener("NetListener1");

}

void NetworkingComponent::_renderNetworkingGUI() {
	ImGui::Begin("Networking");

	static char host[128] = "127.0.0.1";
	static int port = 12345;
	static char message[512] = "";
	static bool autoScroll = true;

	ImGui::TextColored(
			_networkingModule.IsHosting() ? ImVec4(0.0f, 1.0f, 0.0f, 1.0f) :
			_networkingModule.IsConnected() ? ImVec4(0.0f, 1.0f, 1.0f, 1.0f) :
			ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
			"Status: %s",
			_networkingModule.IsHosting() ? "Hosting" :
			_networkingModule.IsConnected() ? "Connected" : "Disconnected"
	);

	ImGui::Separator();
	ImGui::Text("Connection Settings");

	bool isActive = !_networkingModule.IsHosting() && !_networkingModule.IsConnected();

	if (!isActive) {
		ImGui::BeginDisabled();
	}

	ImGui::InputText("Host Address", host, sizeof(host));
	ImGui::InputInt("Port", &port);

	if (ImGui::Button("Host", ImVec2(120, 0)) && isActive) {
		try {
			_networkingModule.Host(port);
			_logBuffer.appendf("[%s] Started hosting on port %d\n",
							   GetTimestamp().c_str(), port);
		} catch (const std::exception& e) {
			_logBuffer.appendf("[%s] Error hosting: %s\n",
							   GetTimestamp().c_str(), e.what());
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("Join", ImVec2(120, 0)) && isActive) {
		try {
			if (_networkingModule.Join(host, port)) {
				_logBuffer.appendf("[%s] Connected to %s:%d\n",
								   GetTimestamp().c_str(), host, port);
			}
		} catch (const std::exception& e) {
			_logBuffer.appendf("[%s] Error joining: %s\n",
							   GetTimestamp().c_str(), e.what());
		}
	}

	if (!isActive) {
		ImGui::EndDisabled();
	}

	if (!isActive) {
		if (ImGui::Button("Disconnect", ImVec2(120, 0))) {
			_networkingModule.Disconnect();
			_logBuffer.appendf("[%s] Disconnected\n", GetTimestamp().c_str());
		}
	}

	ImGui::Separator();
	ImGui::Text("Message");

	if (!isActive) {
		ImGui::InputText("##message", message, sizeof(message));
		if (ImGui::Button("Send", ImVec2(120, 0))) {
			_networkingModule.SendMessage(message);
			_logBuffer.appendf("[%s] Sent: %s\n",
							   GetTimestamp().c_str(), message);
			memset(message, 0, sizeof(message));
		}
	} else {
		ImGui::BeginDisabled();
		ImGui::InputText("##message", message, sizeof(message));
		ImGui::Button("Send", ImVec2(120, 0));
		ImGui::EndDisabled();
	}

	ImGui::Separator();
	ImGui::Text("Log");
	ImGui::Checkbox("Auto-scroll", &autoScroll);
	ImGui::SameLine();
	if (ImGui::Button("Clear")) {
		_logBuffer.clear();
	}

	ImGui::BeginChild("ScrollingRegion", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::TextUnformatted(_logBuffer.begin(), _logBuffer.end());
	if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
		ImGui::SetScrollHereY(1.0f);
	}
	ImGui::EndChild();

	ImGui::End();
}

void NetworkingComponent::_onMessageReceived(const std::string& message) {
	std::cout << "On message received triggered!" << std::endl;
	_logBuffer.appendf("[%s] Received: %s\n", GetTimestamp().c_str(), message.c_str());
}

std::string NetworkingComponent::GetTimestamp() {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	char buffer[32];
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&time));
	return buffer;
}




