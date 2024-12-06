//
// Created by larsv on 12/11/2024.
//

#include "ModuleManager.hpp"

#include "modules/WindowModule.hpp"

ModuleManager* ModuleManager::_instance{nullptr};

ModuleManager* ModuleManager::CreateInstance() {
	auto instance = new ModuleManager();
	_instance = instance;
	return instance;
}

ModuleManager::ModuleManager() : modules{} {
	modules[typeid(WindowModule)] = (std::make_unique<WindowModule>());
}

void ModuleManager::Update(float delta) {
	for (auto& module : modules) module.second->Update(delta);
}
