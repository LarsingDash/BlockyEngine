//
// Created by larsv on 12/11/2024.
//

#include "Transform.hpp"

#include <iostream>

#include "gameObject/GameObject.hpp"

Transform::Transform(GameObject& gameObject) :
		gameObject(gameObject), _position(0.f), _rotation(0.f),
		_scale(1.f), _worldMatrix(1.f), isMarkedForRecalculation(false) {
	RecalculateWorldMatrix();
}

////----- GETTER -----
const glm::vec2& Transform::GetLocalPosition() { return _position; }
const float& Transform::GetLocalRotation() const { return _rotation; }
const glm::vec2& Transform::GetLocalScale() { return _scale; }

glm::vec2 Transform::GetWorldPosition() {
	return {_worldMatrix[0][2], _worldMatrix[1][2]};
}

float Transform::GetWorldRotation() const {
	return atan2f(_worldMatrix[1][0], _worldMatrix[0][0]);
}

glm::vec2 Transform::GetWorldScale() {
	return glm::vec2{
			sqrtf(_worldMatrix[0][0] * _worldMatrix[0][0] + _worldMatrix[0][1] * _worldMatrix[0][1]),
			sqrtf(_worldMatrix[1][0] * _worldMatrix[1][0] + _worldMatrix[1][1] * _worldMatrix[1][1])
	};
}

//----- SETTER -----
void Transform::Translate(const float x, const float y) {
	_position.x += x;
	_position.y += y;
	isMarkedForRecalculation = true;
}

void Transform::Translate(const glm::vec2&& pos) {
	_position += pos;
	isMarkedForRecalculation = true;
}

void Transform::Rotate(const float&& rot) {
	_rotation += rot;
	isMarkedForRecalculation = true;
}

void Transform::Scale(float x, float y) {
	_scale.x += x;
	_scale.y += y;
	isMarkedForRecalculation = true;
}

void Transform::Scale(const glm::vec2&& sca) {
	_scale += sca;
	isMarkedForRecalculation = true;
}

void Transform::RecalculateWorldMatrix() {    // NOLINT(*-no-recursion)
	GameObject* parent = gameObject.parent;

	if (parent) _recalculateWorldMatrix(parent->transform->_worldMatrix);
	else _recalculateWorldMatrix(glm::mat3(1.f)); //Default world matrix for the root

	for (const auto& child : gameObject.GetChildren()) {
		child->transform->RecalculateWorldMatrix();
	}
}

void Transform::_recalculateWorldMatrix(const glm::mat3& parent) {
	//Mark transform as recalculated
	isMarkedForRecalculation = false;

	//Precalculate rotation angles
	float cosTheta = cosf(_rotation);
	float sinTheta = sinf(_rotation);

	//Build matrix
	glm::mat3 localMatrix = glm::mat3(
			_scale.x * cosTheta, -_scale.y * sinTheta, _position.x,
			_scale.x * sinTheta,  _scale.y * cosTheta, _position.y,
			0.0f,                 0.0f,                1.0f
	);

	//Reassign _worldMatrix
	_worldMatrix = parent * localMatrix;
	if (gameObject.tag == "A")
		std::cout << gameObject.tag << ": Local: " << GetLocalPosition().x << "\tWorld: " << GetWorldPosition().x
				  << std::endl;
}
