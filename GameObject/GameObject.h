//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_H
#define BLOCKYENGINE_GAMEOBJECT_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "../Component/Component.h"
#include "Transform.h"

class GameObject {
	public:
		const std::string tag;
		Transform* transform;

		GameObject(std::string  t, Transform* parent)
				: tag(std::move(t)), transform(new Transform(this, parent)) {}

		~GameObject() {
			delete transform;
			std::cout << "removing " << tag << std::endl;
		};
	private:
		std::vector<Component> components;
};

#endif //BLOCKYENGINE_GAMEOBJECT_H
