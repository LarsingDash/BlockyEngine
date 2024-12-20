//
// Created by larsv on 12/11/2024.
//

#include "ModuleManager.hpp"

#include "modules/WindowModule.hpp"
#include "modules/audio/AudioModule.hpp"
#include "modules/physics/PhysicsModule.hpp"
#include "moduleManager/modules/networking/NetworkingModule.hpp"

ModuleManager* ModuleManager::_instance{nullptr};

ModuleManager* ModuleManager::CreateInstance() {
	auto instance = new ModuleManager();
	_instance = instance;
	return instance;
}

ModuleManager::ModuleManager() : modules{} {
	modules[typeid(WindowModule)] = (std::make_unique<WindowModule>());
	modules[typeid(AudioModule)] = (std::make_unique<AudioModule>());
	modules[typeid(PhysicsModule)] = (std::make_unique<PhysicsModule>());
	modules[typeid(NetworkingModule)] = std::make_unique<NetworkingModule>();
}

void ModuleManager::Update(float delta) {
	for (auto& module : modules) module.second->Update(delta);
}
