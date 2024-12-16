//
// Created by 11896 on 11/12/2024.
//
#include "NetworkingModule.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>

NetworkingModule::NetworkingModule() : _isRunning(false), _udpSocket(nullptr) {
	if (SDLNet_Init() == -1) {
		throw std::runtime_error("SDLNet_Init Error: " + std::string(SDLNet_GetError()));
	}
	std::cout << "Networking module initialized." << std::endl;
}

NetworkingModule::~NetworkingModule() {
	Disconnect();
	SDLNet_Quit();
	std::cout << "Networking module cleaned up." << std::endl;
}

void NetworkingModule::Host(Uint16 port) {
	_udpSocket = SDLNet_UDP_Open(port);
	if (!_udpSocket) {
		throw std::runtime_error("Failed to open UDP socket: " + std::string(SDLNet_GetError()));
	}

	_isRunning = true;
	_networkingThread = std::thread(&NetworkingModule::_processIncomingMessages, this);
	std::cout << "Hosting on port " << port << std::endl;
	_isHosting = true;
	_isConnected = true;
}

bool NetworkingModule::Join(const std::string& host, Uint16 port) {
	if (SDLNet_ResolveHost(&_peerAddress, host.c_str(), port) == -1) {
		std::cerr << "Failed to resolve host: " << SDLNet_GetError() << std::endl;
		return false;
	}

	_udpSocket = SDLNet_UDP_Open(0);
	if (!_udpSocket) {
		throw std::runtime_error("Failed to open UDP socket: " + std::string(SDLNet_GetError()));
	}

	_isRunning = true;
	_networkingThread = std::thread(&NetworkingModule::_processIncomingMessages, this);
	std::cout << "Joined host " << host << " on port " << port << std::endl;
	_isConnected = true;
	return true;
}

void NetworkingModule::SendMessage(const std::string& message) {
	if (!_udpSocket) {
		std::cerr << "Cannot send message: UDP socket is not initialized." << std::endl;
		return;
	}

	if (_peerAddress.host == 0 && _peerAddress.port == 0) {
		std::cerr << "Cannot send message: No peer connected." << std::endl;
		return;
	}

	UDPpacket* packet = SDLNet_AllocPacket(512);
	if (!packet) {
		std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
		return;
	}

	if (message.length() + 1 > packet->maxlen) {
		std::cerr << "Message is too long to send." << std::endl;
		SDLNet_FreePacket(packet);
		return;
	}

	std::memcpy(packet->data, message.c_str(), message.length() + 1);
	packet->len = message.length() + 1;
	packet->address = _peerAddress;

	if (SDLNet_UDP_Send(_udpSocket, -1, packet) == 0) {
		std::cerr << "Failed to send packet: " << SDLNet_GetError() << std::endl;
	} else {
		std::cout << "Message sent: " << message << std::endl;
	}

	SDLNet_FreePacket(packet);
}

void NetworkingModule::Disconnect() {
	_isRunning = false;
	if (_networkingThread.joinable()) {
		_networkingThread.join();
	}
	if (_udpSocket) {
		SDLNet_UDP_Close(_udpSocket);
		_udpSocket = nullptr;
	}
	_isHosting = false;
	_isConnected = false;
	std::cout << "Disconnected from network." << std::endl;

}

void NetworkingModule::Update(float delta) {
	std::lock_guard<std::mutex> lock(_messageMutex);
	while (!_incomingMessages.empty()) {
		std::cout << "Received: " << _incomingMessages.front() << std::endl;
		_incomingMessages.pop();
	}
}

void NetworkingModule::_processIncomingMessages() {
	UDPpacket* packet = SDLNet_AllocPacket(512);
	if (!packet) {
		std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
		return;
	}

	while (_isRunning) {
		if (SDLNet_UDP_Recv(_udpSocket, packet)) {
			std::cout << "rceived package!" <<std::endl;
			std::string message(reinterpret_cast<char*>(packet->data));
			_peerAddress = packet->address;
			std::cout << "Notifying " << messageCallbacks.size() << " listeners!" <<std::endl;
			for (const auto& [tag, callback] : messageCallbacks) {
				callback(message);
			}
		}
	}

	SDLNet_FreePacket(packet);
}
bool NetworkingModule::IsHosting() const {
	return _isHosting;
}
bool NetworkingModule::IsConnected() const {
	return _isConnected;
}

void NetworkingModule::AddMessageListener(const std::string& tag, MessageReceivedCallback callback) {
	messageCallbacks[tag] = std::move(callback);
}

void NetworkingModule::RemoveMessageListener(const std::string& tag) {
	messageCallbacks.erase(tag);
}



