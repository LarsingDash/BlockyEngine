//
// Created by 11896 on 11/12/2024.
//
#include "NetworkingModule.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

NetworkingModule::NetworkingModule() : isRunning(false), udpSocket(nullptr) {
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
	udpSocket = SDLNet_UDP_Open(port);
	if (!udpSocket) {
		throw std::runtime_error("Failed to open UDP socket: " + std::string(SDLNet_GetError()));
	}

	isRunning = true;
	networkingThread = std::thread(&NetworkingModule::ProcessIncomingMessages, this);
	std::cout << "Hosting on port " << port << std::endl;
}

bool NetworkingModule::Join(const std::string& host, Uint16 port) {
	if (SDLNet_ResolveHost(&peerAddress, host.c_str(), port) == -1) {
		std::cerr << "Failed to resolve host: " << SDLNet_GetError() << std::endl;
		return false;
	}

	udpSocket = SDLNet_UDP_Open(0);
	if (!udpSocket) {
		throw std::runtime_error("Failed to open UDP socket: " + std::string(SDLNet_GetError()));
	}

	isRunning = true;
	networkingThread = std::thread(&NetworkingModule::ProcessIncomingMessages, this);
	std::cout << "Joined host " << host << " on port " << port << std::endl;
	return true;
}

void NetworkingModule::SendMessage(const std::string& message) {
	if (!udpSocket) {
		std::cerr << "Cannot send message: UDP socket is not initialized." << std::endl;
		return;
	}

	if (peerAddress.host == 0 && peerAddress.port == 0) {
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
	packet->address = peerAddress;

	if (SDLNet_UDP_Send(udpSocket, -1, packet) == 0) {
		std::cerr << "Failed to send packet: " << SDLNet_GetError() << std::endl;
	} else {
		std::cout << "Message sent: " << message << std::endl;
	}

	SDLNet_FreePacket(packet);
}

void NetworkingModule::Disconnect() {
	isRunning = false;
	if (networkingThread.joinable()) {
		networkingThread.join();
	}
	if (udpSocket) {
		SDLNet_UDP_Close(udpSocket);
		udpSocket = nullptr;
	}
	std::cout << "Disconnected from network." << std::endl;
}

void NetworkingModule::Update(float delta) {
	std::lock_guard<std::mutex> lock(messageMutex);
	while (!incomingMessages.empty()) {
		std::cout << "Received: " << incomingMessages.front() << std::endl;
		incomingMessages.pop();
	}
}

void NetworkingModule::ProcessIncomingMessages() {
	UDPpacket* packet = SDLNet_AllocPacket(512);
	if (!packet) {
		std::cerr << "Failed to allocate packet: " << SDLNet_GetError() << std::endl;
		return;
	}

	while (isRunning) {
		if (SDLNet_UDP_Recv(udpSocket, packet)) {
			{
				std::lock_guard<std::mutex> lock(messageMutex);
				incomingMessages.emplace(reinterpret_cast<char*>(packet->data));
				peerAddress = packet->address;
				std::cout << "Incoming message: " << reinterpret_cast<char*>(packet->data) << std::endl;
			}
		}
	}

	SDLNet_FreePacket(packet);
}



