//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_TRANSFORM_H
#define BLOCKYENGINE_TRANSFORM_H

class GameObject;

#include <vector>
#include <algorithm>
#include <memory>
#include "vec2.hpp"

class Transform {
	public:
		GameObject& gameObject;

		explicit Transform(GameObject& gameObject);
		~Transform() = default;

		Transform(const Transform& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		
		Transform(Transform&& other) = delete;
		Transform& operator=(Transform&& other) = delete;
	private:
		//TODO Getter and Setter for Local and World
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;
};


#endif //BLOCKYENGINE_TRANSFORM_H
