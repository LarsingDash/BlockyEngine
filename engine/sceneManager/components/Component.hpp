//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_HPP
#define BLOCKYENGINE_COMPONENT_HPP

#include <string>

class GameObject;

class Component {
	public:
		Component(GameObject& gameObject, const char* tag);
		~Component();

		void Update(float delta);

		std::string tag;
		GameObject& gameObject;
};

#endif //BLOCKYENGINE_COMPONENT_HPP
