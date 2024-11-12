﻿//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_SCENEMANAGER_HPP
#define BLOCKYENGINE_SCENEMANAGER_HPP

#include <vector>
#include <memory>

#include "sceneManager/gameObject/GameObject.hpp"

class SceneManager {
	public:
		SceneManager();
		~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;

		void Update(float delta);

	private:
		std::vector<std::unique_ptr<GameObject>> testScene;
};

#endif //BLOCKYENGINE_SCENEMANAGER_HPP
