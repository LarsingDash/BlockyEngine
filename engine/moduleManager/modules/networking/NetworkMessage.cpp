#include "NetworkMessage.hpp"

#include <stdexcept>
#include <utility>
#include <json/json.hpp>

NetworkMessage::NetworkMessage(MessageType type, std::string payload)
		: _type(type), _payload(std::move(payload)) {}

NetworkMessage NetworkMessage::FromJson(const std::string& jsonStr) {
	try {
		nlohmann::json json = nlohmann::json::parse(jsonStr);
		return NetworkMessage(
				static_cast<MessageType>(json["type"].get<int>()),
				json["payload"].get<std::string>()
		);
	} catch (const std::exception& e) {
		throw std::runtime_error("Failed to parse NetworkMessage: " + std::string(e.what()));
	}
}

std::string NetworkMessage::ToJson() const {
	nlohmann::json json;
	json["type"] = static_cast<int>(_type);
	json["payload"] = _payload;
	return json.dump();
}

MessageType NetworkMessage::GetType() const {
	return _type;
}

const std::string& NetworkMessage::GetPayload() const {
	return _payload;
}

NetworkMessage createConnectMessage(const std::string& clientInfo) {
	return NetworkMessage(MessageType::CONNECT, clientInfo);
}

NetworkMessage createDisconnectMessage(const std::string& reason) {
	return NetworkMessage(MessageType::DISCONNECT, reason);
}
NetworkMessage createConnectionConfirmedMessage(const std::string& reason) {
	return NetworkMessage(MessageType::CONNECTION_CONFIRMED, reason);
}

NetworkMessage createDataMessage(const std::string& data) {
	return NetworkMessage(MessageType::DATA, data);
}

NetworkMessage createHostPingMessage() {
	return NetworkMessage(MessageType::HOST_PING);
}

NetworkMessage createClientPingMessage() {
	return NetworkMessage(MessageType::CLIENT_PING);
}
