//
// Created by 11896 on 11/12/2024.
//

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
	_imguiModule.AddComponent(tag, [this]() {
		_renderNetworkingGUI();
	});

	_networkingModule.AddMessageListener(tag, [this](const NetworkMessage& message) {
		switch (message.GetType()) {
			case MessageType::CONNECT:
				_logBuffer.appendf("[%s] Connected: %s\n",
								   GetTimestamp().c_str(), message.GetPayload().c_str());
				break;
			case MessageType::DISCONNECT:
				_logBuffer.appendf("[%s] Disconnected: %s\n",
								   GetTimestamp().c_str(), message.GetPayload().c_str());
				break;
			case MessageType::CONNECTION_LOST:
				_logBuffer.appendf("[%s] Connection Lost: %s\n",
								   GetTimestamp().c_str(), message.GetPayload().c_str());
				break;
			case MessageType::CONNECTION_CONFIRMED:
				_logBuffer.appendf("[%s] Connection Confirmed From Host: %s\n",
								   GetTimestamp().c_str(), message.GetPayload().c_str());
				break;
			case MessageType::DATA:
				_logBuffer.appendf("[%s] Received Data: %s\n",
								   GetTimestamp().c_str(), message.GetPayload().c_str());
				break;
			default:
				break;
		}
	});
}

void NetworkingComponent::Update(float delta) {
}

void NetworkingComponent::End() {
	_networkingModule.RemoveMessageListener(tag);
	_imguiModule.RemoveComponent(tag);

}

void NetworkingComponent::_renderNetworkingGUI() {
	ImGui::Begin("Networking");

	NetworkRole currentRole = _networkingModule.GetRole();
	bool isConnected = _networkingModule.IsConnected();

	const char* roleStr = "NONE";
	switch (currentRole) {
		case NetworkRole::HOST:   roleStr = "HOST"; break;
		case NetworkRole::CLIENT: roleStr = "CLIENT"; break;
		case NetworkRole::NONE:   roleStr = "NONE"; break;
	}

	ImVec4 roleColor;
	if (currentRole == NetworkRole::HOST) {
		roleColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	} else if (currentRole == NetworkRole::CLIENT) {
		roleColor = ImVec4(0.0f, 0.75f, 1.0f, 1.0f);
	} else {
		roleColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
	}

	ImGui::TextColored(roleColor, "Role: %s", roleStr);


	ImGui::Text("Peer Connected: %s", isConnected ? "YES" : "NO");

	ImGui::Separator();
	ImGui::Text("Connection Settings");

	static char host[128] = "127.0.0.1";
	static int port = 12345;
	static char message[512] = "";
	static bool autoScroll = true;

	bool isActive = (currentRole == NetworkRole::NONE) && !isConnected;

	if (!isActive) {
		ImGui::BeginDisabled();
	}

	ImGui::InputText("Host Address", host, sizeof(host));
	ImGui::InputInt("Port", &port);

	if (ImGui::Button("Host", ImVec2(120, 0)) && isActive) {
		try {
			_networkingModule.Host((Uint16)port);
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
			if (_networkingModule.Connect(host, (Uint16) port)) {
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

	if (currentRole != NetworkRole::NONE || isConnected) {
		if (ImGui::Button("Disconnect", ImVec2(120, 0))) {
			_networkingModule.Disconnect();
			_logBuffer.appendf("[%s] Disconnected\n", GetTimestamp().c_str());
		}
	}

	ImGui::Separator();
	ImGui::Text("Message");

	bool canSendMessages = (currentRole == NetworkRole::HOST && isConnected) ||
			(currentRole == NetworkRole::CLIENT && isConnected);

	if (!canSendMessages) {
		ImGui::BeginDisabled();
	}

	ImGui::InputText("##message", message, sizeof(message));
	if (ImGui::Button("Send", ImVec2(120, 0))) {
		_networkingModule.SendData(message);
		_logBuffer.appendf("[%s] Sent: %s\n", GetTimestamp().c_str(), message);
		memset(message, 0, sizeof(message));
	}

	if (!canSendMessages) {
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

std::string NetworkingComponent::GetTimestamp() {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	char buffer[32];
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&time));
	return buffer;
}





