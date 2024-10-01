//
// Created by larsv on 23/09/2024.
//

#include "Transform.hpp"
#include "../GameObject/GameObject.hpp"
#include "gtc/matrix_transform.hpp"

Transform::Transform(GameObject& gameObject) :
		gameObject(gameObject), position{0.f},
		rotation(0), scale{1.f}, worldMatrix{1.f} {
	worldMatrix = RecalculateWoldMatrix();
}

////----- GETTER -----
const glm::vec2& Transform::GetLocalPosition() { return position; }

const float& Transform::GetLocalRotation() const { return rotation; }

const glm::vec2& Transform::GetLocalScale() { return scale; }

//----- SETTER -----
void Transform::SetLocalPosition(const float x, const float y) {
	position.x = x;
	position.y = y;
	RefreshWorldMatrix();
}

void Transform::SetLocalPosition(const glm::vec2&& pos) { SetLocalPosition(pos.x, pos.y); }

void Transform::SetLocalRotation(const float&& rot) {
	rotation = rot;
	RefreshWorldMatrix();
}

void Transform::SetLocalScale(float x, float y) {
	scale.x = x;
	scale.y = y;
	RefreshWorldMatrix();
}

void Transform::SetLocalScale(const glm::vec2&& sca) { SetLocalScale(sca.x, sca.y); }

//----- WORLD -----
glm::vec2 Transform::GetWorldPosition() {
	return worldMatrix[2];
}

float Transform::GetWorldRotation() {
	return atan2f(worldMatrix[0][1], worldMatrix[0][0]);
}

glm::vec2 Transform::GetWorldScale() {
	glm::vec2 sca;
	sca.x = glm::length(glm::vec2(worldMatrix[0]));
	sca.y = glm::length(glm::vec2(worldMatrix[1]));
	return sca;
}

void Transform::RefreshWorldMatrix() {
	//Refresh own matrix
	worldMatrix = RecalculateWoldMatrix();

	//Refresh matrix of all children
	for (const auto& child: gameObject.GetChildren())
		child->transform->RefreshWorldMatrix();
}

glm::mat3 Transform::RecalculateWoldMatrix() {
	//Break recursion on root
	if (!gameObject.parent) return worldMatrix;

	//Create matrix
	auto translationMatrix = glm::mat3(1.0f);

	//POSITION
	translationMatrix[2] = glm::vec3(position, 1.0f);

	//ROTATION
	float cosTheta = cosf(rotation);
	float sinTheta = sinf(rotation);
	glm::mat3 rotationMatrix = glm::mat3(
			cosTheta, -sinTheta, 0.0f,
			sinTheta, cosTheta, 0.0f,
			0.0f, 0.0f, 1.0f
	);

	//SCALE
	glm::mat3 scaleMatrix = glm::mat3(
			scale.x, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f,
			0.0f, 0.0f, 1.0f
	);

	//Combine segments
	glm::mat3 localTransform = translationMatrix * rotationMatrix * scaleMatrix;

	//Chain recursive call to parents to get world transformation
	return gameObject.parent->transform->RecalculateWoldMatrix() * localTransform;
}