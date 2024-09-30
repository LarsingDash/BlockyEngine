//
// Created by larsv on 23/09/2024.
//

#include "Transform.h"
#include "../GameObject/GameObject.h"

Transform::Transform(GameObject& gameObject) : gameObject(gameObject),
											   position(), rotation(), scale() {}

