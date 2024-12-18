#include "NetworkMessage.hpp"
#include <stdexcept>
#include <utility>
#include <nlohmann/json.hpp>

NetworkMessage::NetworkMessage(MessageType type, std::string payload)
		: type(type), payload(std::move(payload)) {}

NetworkMessage NetworkMessage::fromJson(const std::string& jsonStr) {
	try {
		nlohmann::json j = nlohmann::json::parse(jsonStr);
		return NetworkMessage(
				static_cast<MessageType>(j["type"].get<int>()),
				j["payload"].get<std::string>()
		);
	} catch (const std::exception& e) {
		throw std::runtime_error("Failed to parse NetworkMessage: " + std::string(e.what()));
	}
}

std::string NetworkMessage::toJson() const {
	nlohmann::json j;
	j["type"] = static_cast<int>(type);
	j["payload"] = payload;
	return j.dump();
}

MessageType NetworkMessage::getType() const {
	return type;
}

const std::string& NetworkMessage::getPayload() const {
	return payload;
}

NetworkMessage createConnectMessage(const std::string& clientInfo) {
	return NetworkMessage(MessageType::CONNECT, clientInfo);
}

NetworkMessage createDisconnectMessage(const std::string& reason) {
	return NetworkMessage(MessageType::DISCONNECT, reason);
}

NetworkMessage createConnectionLostMessage(const std::string& details) {
	return NetworkMessage(MessageType::CONNECTION_LOST, details);
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
