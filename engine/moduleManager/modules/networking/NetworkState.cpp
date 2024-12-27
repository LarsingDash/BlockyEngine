//
// Created by 11896 on 18/12/2024.
//

#include "NetworkState.hpp"

NetworkState::NetworkState()
		: _role(NetworkRole::NONE),
		  _lastClientPingTime(std::chrono::steady_clock::time_point::min()),
		  _lastHostPingTime(std::chrono::steady_clock::time_point::min()) {}

void NetworkState::SetRole(NetworkRole newRole) {
	std::lock_guard<std::mutex> lock(_stateMutex);
	_role = newRole;
}

NetworkRole NetworkState::GetRole() const {
	std::lock_guard<std::mutex> lock(_stateMutex);
	return _role;
}

void NetworkState::OnHostPingReceived() {
	std::lock_guard<std::mutex> lock(_stateMutex);
	_lastHostPingTime = std::chrono::steady_clock::now();
}

void NetworkState::OnClientPingReceived() {
	std::lock_guard<std::mutex> lock(_stateMutex);
	_lastClientPingTime = std::chrono::steady_clock::now();
}

bool NetworkState::IsClientConnected() const {
	std::lock_guard<std::mutex> lock(_stateMutex);
	if (_role != NetworkRole::HOST) {
		return false;
	}
	return _isRecent(_lastClientPingTime);
}

bool NetworkState::IsHostConnected() const {
	std::lock_guard<std::mutex> lock(_stateMutex);
	if (_role != NetworkRole::CLIENT) {
		return false;
	}
	return _isRecent(_lastHostPingTime);
}

bool NetworkState::_isRecent(std::chrono::steady_clock::time_point timestamp) {
	if (timestamp == std::chrono::steady_clock::time_point::min()) {
		return false;
	}
	auto now = std::chrono::steady_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count();
	return diff <= 3;
}