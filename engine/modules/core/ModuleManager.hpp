//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_MODULEMANAGER_HPP
#define BLOCKYENGINE_MODULEMANAGER_HPP

#include <memory>
#include <array>

#include "modules/core/ModuleWrapper.hpp"

class ModuleManager {
	public:
		ModuleManager();
		~ModuleManager() = default;

		ModuleManager(const ModuleManager& other) = delete;
		ModuleManager& operator=(const ModuleManager& other) = delete;
		ModuleManager(ModuleManager&& other) noexcept = delete;
		ModuleManager& operator=(ModuleManager&& other) noexcept = delete;

		void Update(float delta);

	private:
		std::array<std::unique_ptr<ModuleWrapper>, 1> modules;
};

#endif //BLOCKYENGINE_MODULEMANAGER_HPP
