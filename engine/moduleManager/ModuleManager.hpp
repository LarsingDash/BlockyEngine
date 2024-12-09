//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_MODULEMANAGER_HPP
#define BLOCKYENGINE_MODULEMANAGER_HPP

#include <typeindex>
#include <memory>
#include <unordered_map>
#include <stdexcept>

#include "moduleManager/ModuleWrapper.hpp"

/// Manager of all Blocky Engine's module. All modules inherit from ModuleWrapper.
/// The ModuleManager uses the Singleton design pattern, meaning only one static instance exists.
/// The only instance of ModuleManager that should exist, is automatically managed by the only BlockyEngine instance
class ModuleManager {
	public:
		/// Internally used by BlockyEngine to create the Singleton instance and gain ownership over it
		/// \return Raw pointer to the heap allocation for this ModuleManager. Can be used to wrap a unique_ptr around
		static ModuleManager* CreateInstance();
		
		/// ModuleManager is a singleton class, this method gets the only existing instance
		/// \return Reference to the ModuleManager
		inline static ModuleManager& GetInstance() { return *_instance; }
		~ModuleManager() = default;

		ModuleManager(const ModuleManager& other) = delete;
		ModuleManager& operator=(const ModuleManager& other) = delete;
		ModuleManager(ModuleManager&& other) noexcept = delete;
		ModuleManager& operator=(ModuleManager&& other) noexcept = delete;

		/// Called internally from the BlockyEngine's cycle, never use manually.
		/// This method cascade the update cycle to all Modules. It is called every frame, immediately after the active scene is updated
		/// \param delta Difference in time since the last Update call 
		void Update(float delta);

		/// Attempts to get the module, based on the given template parameter
		/// \tparam T The type of module to get, must inherit from ModuleWrapper
		/// \return A reference to the instance of the requested module, managed by the ModuleManager 
		/// \throws runtime_error Thrown if the requested module was not found. Should never happen but theoretically possible 
		template<typename T>
		T& GetModule() {
			static_assert(std::is_base_of<ModuleWrapper, T>::value, "T must inherit from ModuleWrapper");

			//Try to find the module based on the given type
			auto& type = typeid(T);
			auto it = modules.find(type);

			//Return the requested module, if none was found: throw an error indicating so
			if (it == modules.end()) throw std::runtime_error("Requested module not found in the modules map");
			return dynamic_cast<T&>(*modules[type]);
		}

	private:
		static ModuleManager* _instance;
		
		ModuleManager();
		std::unordered_map<std::type_index, std::unique_ptr<ModuleWrapper>> modules;
};

#endif //BLOCKYENGINE_MODULEMANAGER_HPP