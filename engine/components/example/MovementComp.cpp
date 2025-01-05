//
// Created by larsv on 29/11/2024.
//

#include "MovementComp.hpp"

#include "gameObject/GameObject.hpp"
#include "glm/trigonometric.hpp"

MovementComp::MovementComp(GameObject* gameObject, const char* tag, float distance) :
		Component(gameObject, tag), _direction(1, 0), _distance(distance), _speed(20.f) {}

MovementComp::~MovementComp() = default;

Component* MovementComp::_clone(const GameObject& parent) {
	auto clone = new MovementComp(*this);
	return clone;
}

void MovementComp::Start() {}

void MovementComp::Update(float delta) {
	gameObject->transform->Translate(_direction.x * delta * _speed, _direction.y * delta * _speed);
	if (glm::distance(gameObject->transform->GetLocalPosition(), glm::vec2{0}) >= _distance) {
		gameObject->Destroy();
	}
}

void MovementComp::End() {}

void MovementComp::SetDirectionByAngle(float angle) {
	float radians = glm::radians(angle);

	_direction.x = std::cos(radians);
	_direction.y = std::sin(radians);
}

JSON_REGISTER_FROM(
		MovementComp,
		[](const nlohmann::json& json, MovementComp& other) {
			other._direction.x = json.at("x").get<float>();
			other._direction.y = json.at("y").get<float>();
			other._distance = json.at("distance").get<float>();
		}
)

JSON_REGISTER_TO(
		MovementComp,
		[](nlohmann::json& json, const MovementComp& other) {
			json["x"] = other._direction.x;
			json["y"] = other._direction.y;
			json["distance"] = other._distance;
		}
)
