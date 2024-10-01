//
// Created by larsv on 23/09/2024.
//

#include "Transform.hpp"
#include "../GameObject/GameObject.hpp"

Transform::Transform(GameObject& gameObject) : gameObject(gameObject),
											   position(), rotation(), scale() {}

