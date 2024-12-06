//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_SCENEMANAGER_HPP
#define BLOCKYENGINE_SCENEMANAGER_HPP

#include <vector>
#include <memory>

#include "gameObject/GameObject.hpp"

/// Manages Scenes like prefabs, stored simply by the root GameObject of this scene.
/// They are created once, before calling Run() on BlockyEngine,
/// and then they can be instantiated over and over to get the scene in a clean starting state
class SceneManager {
	public:
		~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = default;
		SceneManager& operator=(SceneManager&& other) noexcept = default;

		/// Internally used by BlockyEngine to create the Singleton instance and gain ownership over it
		/// \return Raw pointer to the heap allocation for this SceneManager. Can be used to wrap a unique_ptr around
		static SceneManager* CreateInstance();
		/// SceneManager is a singleton class, this method gets the only existing instance
		/// \return Reference to the SceneManager
		inline static SceneManager& GetInstance() { return *_instance; }

		/// Registers the given scene in this SceneManager by move, so use std::move() when calling this method
		/// \param scene The scene (including wrapping unique_ptr) that will be moved to the list of scenes in this Manager 
		void AddScene(std::unique_ptr<GameObject>&& scene);
		/// Removes a scene by the tag. If no scene root with that tag could be found, nothing happens
		/// \param target The tag of the root of the scene that should be removed
		void RemoveScene(const std::string& target);
		/// Switches to the scene by the given tag. If no scene root with that tag could be found, an error will be printed (not thrown) and nothing happens
		/// Calling SwitchUpdate from a Component will only set a temporary target, which will actually be switched to at the start of the next frame  
		/// \param tag The tag of the root of the scene that should be switched to
		void SwitchScene(const std::string& tag);

		/// Internally used by BlockyEngine to cascade the update cycle to all GameObjects (and thus components) in the currently active scene.
		/// Called every frame, all modules are updated immediately after
		/// \param delta Difference in time since last Update call  
		void Update(float delta);

	private:
		SceneManager();
		static SceneManager* _instance;

		/// Internal method for switching scene, called at the start of Update() if _switchTarget was not empty.
		/// Clears _switchTarget at the end, regardless of if the targeted scene was found
		void _switchScene();
		std::string _switchTarget;

		std::vector<std::unique_ptr<GameObject>> _scenes;
		std::unique_ptr<GameObject> _activeScene;
		std::vector<std::reference_wrapper<Transform>> _recalculationList;
};

#endif //BLOCKYENGINE_SCENEMANAGER_HPP