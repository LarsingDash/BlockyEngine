//
// Created by 11896 on 17/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKMESSAGE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKMESSAGE_HPP_
#include <string>
#include <stdexcept>
#include <utility>

enum class MessageType {
	CONNECT,
	DISCONNECT,
	CONNECTION_LOST,
	DATA,
	HOST_PING,
	CLIENT_PING
};

class NetworkMessage {
	public:
		explicit NetworkMessage(MessageType type, std::string payload = "");

		static NetworkMessage fromJson(const std::string& jsonStr);

		[[nodiscard]] std::string toJson() const;
		[[nodiscard]] MessageType getType() const;
		[[nodiscard]] const std::string& getPayload() const;

	private:
		MessageType type;
		std::string payload;
};

NetworkMessage createConnectMessage(const std::string& clientInfo = "");
NetworkMessage createDisconnectMessage(const std::string& reason = "");
NetworkMessage createConnectionLostMessage(const std::string& details = "");
NetworkMessage createDataMessage(const std::string& data);
NetworkMessage createHostPingMessage();
NetworkMessage createClientPingMessage();


#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKMESSAGE_HPP_
