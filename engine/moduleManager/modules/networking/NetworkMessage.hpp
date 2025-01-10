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
	CONNECTION_CONFIRMED,
	DATA,
	HOST_PING,
	CLIENT_PING
};

class NetworkMessage {
	public:
		explicit NetworkMessage(MessageType type, std::string payload = "");

		static NetworkMessage FromJson(const std::string& jsonStr);
		[[nodiscard]] std::string ToJson() const;
		[[nodiscard]] MessageType GetType() const;
		[[nodiscard]] const std::string& GetPayload() const;

	private:
		MessageType _type;
		std::string _payload;
};

//Helper create message funcs
NetworkMessage createConnectMessage(const std::string& clientInfo = "");
NetworkMessage createDisconnectMessage(const std::string& reason = "");
NetworkMessage createConnectionConfirmedMessage(const std::string& details = "");
NetworkMessage createDataMessage(const std::string& data);
NetworkMessage createHostPingMessage();
NetworkMessage createClientPingMessage();


#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKMESSAGE_HPP_
