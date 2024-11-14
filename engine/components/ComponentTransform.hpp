//
// Created by larsv on 13/11/2024.
//

#ifndef BLOCKYENGINE_COMPONENTTRANSFORM_HPP
#define BLOCKYENGINE_COMPONENTTRANSFORM_HPP

#include "glm/vec2.hpp"

class ComponentTransform {
	public:
		ComponentTransform();
		
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;
};

#endif //BLOCKYENGINE_COMPONENTTRANSFORM_HPP