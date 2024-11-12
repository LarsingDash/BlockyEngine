//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_HPP
#define BLOCKYENGINE_GAMEOBJECT_HPP

#include <string>
#include <memory>

#include "sceneManager/gameObject/Transform.hpp"

class GameObject {
	public:
		const std::string tag;

		std::unique_ptr<Transform> transform;

		//----- RULE OF FIVE
		explicit GameObject(std::string tag);
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(const GameObject&& other) = delete;
		GameObject& operator=(const GameObject&& other) = delete;

		//----- CYCLE
		void Update(float delta);
};

#endif //BLOCKYENGINE_GAMEOBJECT_HPP
