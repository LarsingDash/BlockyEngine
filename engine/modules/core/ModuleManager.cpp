//
// Created by larsv on 12/11/2024.
//

#include "ModuleManager.hpp"

#include "modules/WindowModule.hpp"

ModuleManager::ModuleManager() : modules{} {
	modules[0] = (std::make_unique<WindowModule>());
}

void ModuleManager::Update(float delta) {
	for (auto& module: modules) module->Update(delta);
}
