//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_SCENEMANAGER_HPP
#define BLOCKYENGINE_SCENEMANAGER_HPP

#include <vector>
#include <memory>

#include "gameObject/GameObject.hpp"
#include "moduleManager/modules/input/InputModule.hpp"
#include "components/renderables/RectangleRenderable.hpp"

class SceneManager {
	public:
		SceneManager();
		~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = default;
		SceneManager& operator=(SceneManager&& other) noexcept = default;

		void AddScene(std::unique_ptr<GameObject>&& scene);
		void SwitchScene(const std::string& tag);
		void Update(float delta);

	private:
		std::vector<std::unique_ptr<GameObject>> _scenes;
		std::unique_ptr<GameObject> _activeScene;
		std::vector<std::reference_wrapper<Transform>> _recalculationList;
};

#endif //BLOCKYENGINE_SCENEMANAGER_HPP