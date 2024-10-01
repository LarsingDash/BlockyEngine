//
// Created by larsv on 24/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECTMANAGER_HPP
#define BLOCKYENGINE_GAMEOBJECTMANAGER_HPP

#include <vector>
#include <memory>
#include "GameObject.hpp"

class GameObjectManager {
	public:
		GameObjectManager();
		void OnUpdate(float delta);
		~GameObjectManager() = default;
	private:
		std::unique_ptr<GameObject> sceneRoot;
};


#endif //BLOCKYENGINE_GAMEOBJECTMANAGER_HPP
