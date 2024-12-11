//
// Created by 11896 on 11/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_

#include <string>
#include <vector>
#include "SDL_net.h"
#include "moduleManager/ModuleWrapper.hpp"

struct PeerConnection {
	TCPsocket socket;
	IPaddress address;
};


class NetworkingModule : public ModuleWrapper {
	public:
		NetworkingModule();
		~NetworkingModule() override;

		void Update(float delta) override;



};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_NETWORKING_NETWORKINGMODULE_HPP_
