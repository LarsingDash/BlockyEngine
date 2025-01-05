//
// Created by 11896 on 18/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKSTATE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKSTATE_HPP_

#include <chrono>
#include <mutex>

enum class NetworkRole {
	NONE,
	CLIENT,
	HOST
};

class NetworkState {
	public:
		NetworkState();

		void SetRole(NetworkRole newRole);
		NetworkRole GetRole() const;

		void OnHostPingReceived();
		void OnClientPingReceived();
		bool IsClientConnected() const;
		bool IsHostConnected() const;

	private:
		static bool _isRecent(std::chrono::steady_clock::time_point timestamp) ;

		mutable std::mutex _stateMutex;
		NetworkRole _role;

		std::chrono::steady_clock::time_point _lastClientPingTime;
		std::chrono::steady_clock::time_point _lastHostPingTime;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKSTATE_HPP_
