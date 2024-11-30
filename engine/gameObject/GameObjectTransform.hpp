//
// Created by larsv on 22/11/2024.
//

#include "gameObject/Transform.hpp"

#ifndef BLOCKYENGINE_ENGINE_GAMEOBJECT_GAMEOBJECTTRANSFORM_HPP_
#define BLOCKYENGINE_ENGINE_GAMEOBJECT_GAMEOBJECTTRANSFORM_HPP_

class GameObjectTransform : public Transform {
	public:
		explicit GameObjectTransform(GameObject& gameObject);
		void RecalculateWorldMatrix() override;
};

#endif //BLOCKYENGINE_ENGINE_GAMEOBJECT_GAMEOBJECTTRANSFORM_HPP_
