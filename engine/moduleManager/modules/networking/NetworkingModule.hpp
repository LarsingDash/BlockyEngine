//
// Created by 11896 on 11/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include "SDL_net.h"
#include "moduleManager/ModuleWrapper.hpp"


class NetworkingModule : public ModuleWrapper {
	public:
		NetworkingModule();
		~NetworkingModule();

		using MessageReceivedCallback = std::function<void(const std::string&)>;

		void AddMessageListener(MessageReceivedCallback callback);
		void RemoveMessageListener(MessageReceivedCallback callback);

		void Host(Uint16 port);
		bool Join(const std::string& host, Uint16 port);
		void SendMessage(const std::string& message);
		void Disconnect();
		bool IsHosting() const;
		bool IsConnected() const;
		void Update(float delta) override;

	private:
		void ProcessIncomingMessages();
		bool isHosting = false;
		bool isConnected = false;


		std::vector<MessageReceivedCallback> messageCallbacks;
		UDPsocket udpSocket;
		IPaddress peerAddress;
		std::thread networkingThread;
		std::mutex messageMutex;
		std::queue<std::string> incomingMessages;
		bool isRunning;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_
