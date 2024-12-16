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
		~NetworkingModule() override;

		using MessageReceivedCallback = std::function<void(const std::string&)>;

		void AddMessageListener(const std::string& tag, MessageReceivedCallback callback);
		void RemoveMessageListener(const std::string& tag);

		void Host(Uint16 port);
		bool Join(const std::string& host, Uint16 port);
		void SendMessage(const std::string& message);
		void Disconnect();
		bool IsHosting() const;
		bool IsConnected() const;
		void Update(float delta) override;

	private:
		void _processIncomingMessages();
		bool _isHosting = false;
		bool _isConnected = false;
		bool _isRunning;


		std::unordered_map<std::string, MessageReceivedCallback> messageCallbacks;
		UDPsocket _udpSocket;
		IPaddress _peerAddress;
		std::thread _networkingThread;
		std::mutex _messageMutex;
		std::queue<std::string> _incomingMessages;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_
