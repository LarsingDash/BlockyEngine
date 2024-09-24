//
// Created by larsv on 24/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECTMANAGER_H
#define BLOCKYENGINE_GAMEOBJECTMANAGER_H

#include <vector>
#include "GameObject.h"

class GameObjectManager {
	public:
		GameObjectManager();
		void OnUpdate(float delta);
		~GameObjectManager();
	private:
		GameObject* sceneRoot;		
};


#endif //BLOCKYENGINE_GAMEOBJECTMANAGER_H
