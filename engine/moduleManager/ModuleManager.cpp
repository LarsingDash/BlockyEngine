﻿//
// Created by larsv on 12/11/2024.
//

#include "ModuleManager.hpp"

#include "modules/WindowModule.hpp"
// #include "modules/physics/PhysicsModule.hpp"

ModuleManager& ModuleManager::getInstance() {
	static ModuleManager instance;
	return instance;
}

ModuleManager::ModuleManager() : modules{} {
	modules[typeid(WindowModule)] = (std::make_unique<WindowModule>());
	// modules[typeid(PhysicsModule)] = (std::make_unique<PhysicsModule>());
}

void ModuleManager::Update(float delta) {
	for (auto& module : modules) module.second->Update(delta);
}
