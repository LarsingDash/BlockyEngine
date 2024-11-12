//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_MODULEMANAGER_HPP
#define BLOCKYENGINE_MODULEMANAGER_HPP

#include <typeindex>
#include <memory>
#include <unordered_map>
#include <stdexcept>

#include "modules/core/ModuleWrapper.hpp"

class ModuleManager {
	public:		
		static ModuleManager& getInstance();
		~ModuleManager() = default;

		ModuleManager(const ModuleManager& other) = delete;
		ModuleManager& operator=(const ModuleManager& other) = delete;
		ModuleManager(ModuleManager&& other) noexcept = delete;
		ModuleManager& operator=(ModuleManager&& other) noexcept = delete;

		void Update(float delta);

		template<typename T>
		T& getModule() {
			static_assert(std::is_base_of<ModuleWrapper, T>::value, "T must inherit from ModuleWrapper");
			
			//Try to find the module based on the given type
			auto& type = typeid(T);
			auto it = modules.find(type);
			
			//Return the requested module, if none was found: throw an error indicating so
			if (it == modules.end()) throw std::runtime_error("Requested module not found in the modules map");
			return modules[type];
		}
		
	private:
		ModuleManager();
		std::unordered_map<std::type_index, std::unique_ptr<ModuleWrapper>> modules;
};

#endif //BLOCKYENGINE_MODULEMANAGER_HPP
