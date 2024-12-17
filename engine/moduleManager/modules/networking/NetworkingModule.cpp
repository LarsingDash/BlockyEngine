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
}

NetworkingModule::~NetworkingModule() {
	Disconnect();
	SDLNet_Quit();
}

void NetworkingModule::Host(Uint16 port) {
	if (_isRunning) return;

	_udpSocket = SDLNet_UDP_Open(port);
	if (!_udpSocket) {
		throw std::runtime_error("Failed to open UDP socket: " + std::string(SDLNet_GetError()));
	}

	_isRunning = true;
	_isHosting = true;
	_isConnected = false;
	_networkingThread = std::thread(&NetworkingModule::_processIncomingMessages, this);

	std::cout << "Hosting on port " << port << std::endl;
}

bool NetworkingModule::Join(const std::string& host, Uint16 port) {
	if (_isRunning) return false;

	if (SDLNet_ResolveHost(&_peerAddress, host.c_str(), port) == -1) {
		std::cerr << "Failed to resolve host: " << SDLNet_GetError() << std::endl;
		return false;
	}

	_udpSocket = SDLNet_UDP_Open(0);
	if (!_udpSocket) {
		throw std::runtime_error("Failed to open UDP socket: " + std::string(SDLNet_GetError()));
	}

	_isRunning = true;
	_isHosting = false;
	_isConnected = true;

	_networkingThread = std::thread(&NetworkingModule::_processIncomingMessages, this);

	SendMessage(createConnectMessage("Client joined"));

	return true;
}

void NetworkingModule::SendMessage(const NetworkMessage& message) {
	if (!_udpSocket) {
		std::cerr << "Cannot send message: UDP socket is not initialized." << std::endl;
		return;
	}

	std::string jsonStr = message.toJson();
	UDPpacket* packet = SDLNet_AllocPacket(512);

	if (!packet || jsonStr.length() + 1 > packet->maxlen) {
		std::cerr << "Failed to allocate or oversized packet." << std::endl;
		if (packet) SDLNet_FreePacket(packet);
		return;
	}

	std::memcpy(packet->data, jsonStr.c_str(), jsonStr.length() + 1);
	packet->len = jsonStr.length() + 1;
	packet->address = _peerAddress;

	if (SDLNet_UDP_Send(_udpSocket, -1, packet) == 0) {
		std::cerr << "Failed to send packet: " << SDLNet_GetError() << std::endl;
	}

	SDLNet_FreePacket(packet);
}

void NetworkingModule::Disconnect() {
	{
		std::lock_guard<std::mutex> lock(_messageMutex);
		if (_isConnected) SendMessage(createDisconnectMessage("Disconnecting peer"));
		_isRunning = false;
		_isConnected = false;
		_isHosting = false;
	}

	if (_networkingThread.joinable()) _networkingThread.join();
	if (_udpSocket) SDLNet_UDP_Close(_udpSocket);

	_udpSocket = nullptr;
	_peerAddress = {};
}

void NetworkingModule::Update(float delta) {
	std::lock_guard<std::mutex> lock(_messageMutex);
	while (!_incomingMessages.empty()) {
		NetworkMessage& message = _incomingMessages.front();
		for (const auto& [tag, callback] : messageCallbacks) {
			callback(message);
		}
		_incomingMessages.pop();
	}
}

void NetworkingModule::_processIncomingMessages() {
	UDPpacket* packet = SDLNet_AllocPacket(512);
	if (!packet) return;

	while (_isRunning) {
		if (SDLNet_UDP_Recv(_udpSocket, packet)) {
			try {
				std::string jsonStr(reinterpret_cast<char*>(packet->data));
				NetworkMessage message = NetworkMessage::fromJson(jsonStr);

				if (_isHosting && !_isConnected) {
					_peerAddress = packet->address;
					_isConnected = true;
				}

				{
					std::lock_guard<std::mutex> lock(_messageMutex);
					_incomingMessages.push(message);
				}

			} catch (const std::exception& e) {
				std::cerr << "Error processing message: " << e.what() << std::endl;
			}
		}
	}

	SDLNet_FreePacket(packet);
}

void NetworkingModule::AddMessageListener(const std::string& tag, MessageReceivedCallback callback) {
	messageCallbacks[tag] = std::move(callback);
}

void NetworkingModule::RemoveMessageListener(const std::string& tag) {
	messageCallbacks.erase(tag);
}

bool NetworkingModule::IsHosting() const {
	return _isHosting;
}

bool NetworkingModule::IsConnected() const {
	return _isConnected;
}
