//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(std::string tag) :
		tag{std::move(tag)}, transform{std::make_unique<Transform>()} {
}

void GameObject::Update(float delta) {
	std::cout << "test" << std::endl;
}
