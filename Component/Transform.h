//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_TRANSFORM_H
#define BLOCKYENGINE_TRANSFORM_H

//Forward declaration to resolve circular dependence
class GameObject;

#include <vector>
#include <algorithm>
#include "vec2.hpp"

class Transform {
	public:
		GameObject* gameObject;
		Transform* parent;

		Transform(GameObject* gameObject, Transform* parent);
		~Transform();

		[[nodiscard]] const std::vector<Transform*>& getChildren() const {
			return children;
		}
		
		void removeChild(Transform* transform);
		void setParent(Transform* transform);

	private:
		std::vector<Transform*> children;

		//TODO Getter and Setter for Local and World
		glm::vec2 position;
		glm::vec2 rotation;
		glm::vec2 scale;
};


#endif //BLOCKYENGINE_TRANSFORM_H
