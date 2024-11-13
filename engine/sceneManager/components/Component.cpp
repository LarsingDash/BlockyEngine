﻿//
// Created by larsv on 12/11/2024.
//

#include "sceneManager/gameObject/GameObject.hpp"
#include "Component.hpp"

#include <iostream>

Component::Component(GameObject& gameObject, const char* tag) :
		gameObject{gameObject}, tag{tag}, componentTransform{
		std::make_unique<ComponentTransform>()} {}

Component::~Component() = default;
