//
// Created by larsv on 12/11/2024.
//

#include "Transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

#include "gameObject/GameObject.hpp"

Transform::Transform(GameObject& gameObject) :
		gameObject(gameObject), parent(nullptr),
		_position(0.f), _rotation(0.f), _scale(1.f),
		_worldPosition(_position), _worldRotation(_rotation), _worldScale(_scale),
		_worldMatrix(1.f), isMarkedForRecalculation(false) {
}

////----- GETTER -----
const glm::vec2& Transform::GetLocalPosition() const { return _position; }
[[maybe_unused]] float Transform::GetLocalRotation() const { return _rotation * (180.0f / static_cast<float>(M_PI)); }
const glm::vec2& Transform::GetLocalScale() const { return _scale; }

const glm::vec2& Transform::GetWorldPosition() const { return _worldPosition; }
[[maybe_unused]] float Transform::GetWorldRotation() const { return _worldRotation * (180.0f / static_cast<float>(M_PI)); }
const glm::vec2& Transform::GetWorldScale() const { return _worldScale; }

//----- SETTER -----
void Transform::Translate(const float x, const float y) {
	_position.x += x;
	_position.y += y;
	isMarkedForRecalculation = true;
}

void Transform::Rotate(float rotation) {
	_rotation -= rotation * (static_cast<float>(M_PI) / 180.0f);
	isMarkedForRecalculation = true;
}

void Transform::Scale(float x, float y) {
	_scale.x += x;
	_scale.y += y;
	isMarkedForRecalculation = true;
}

void Transform::SetPosition(float x, float y) {
	_position.x = x;
	_position.y = y;
	isMarkedForRecalculation = true;
}

void Transform::SetRotation(float rotation) {
	_rotation = -(rotation * (static_cast<float>(M_PI) / 180.0f));
	isMarkedForRecalculation = true;
}

void Transform::SetScale(float x, float y) {
	_scale.x = x;
	_scale.y = y;
	isMarkedForRecalculation = true;
}

//----- WORLD -----
void Transform::_recalculateWorldMatrix() {
	isMarkedForRecalculation = false;

	//Build local matrix
	auto localMatrix = glm::mat3(1.0f);
	localMatrix = glm::translate(localMatrix, _position);
	localMatrix = glm::rotate(localMatrix, _rotation);
	localMatrix = glm::scale(localMatrix, _scale);

	//Parent check for root: Assign worldMatrix and Rotation and Scale
	if (parent) {
		_worldMatrix = parent->_worldMatrix * localMatrix;
		_worldRotation = parent->_worldRotation + _rotation;
		_worldScale = parent->_worldScale * _scale;
	} else {
		_worldMatrix = localMatrix;
		_worldRotation = _rotation;
		_worldScale = _scale;
	}

	//Location can be simply extracted, regardless of scale and rotation
	_worldPosition = glm::vec2(_worldMatrix[2][0], _worldMatrix[2][1]);
}
