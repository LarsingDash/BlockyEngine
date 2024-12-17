//
// Created by hmkam on 28/11/2024.
//

#include "BoxRigidBody.hpp"

#include <components/physics/shape/Box.hpp>
#include <gameObject/GameObject.hpp>

// BoxRigidBody::BoxRigidBody(GameObject* gameObject, const char* tag, bool isStatic, glm::vec2 velocity,
//                            float rotationVelocity, float angularResistance, float linearResistance,
//                            bool gravityEnabled) : BoxRigidBody(gameObject, tag, isStatic, velocity, rotationVelocity,
//                                                                angularResistance, linearResistance, gravityEnabled,
//                                                                gameObject->transform->GetWorldScale().y,
//                                                                gameObject->transform->GetWorldScale().x) {}

// BoxRigidBody::BoxRigidBody(GameObject* gameObject, const char* tag, const TypeProperties& properties): BoxRigidBody(
// 	gameObject, tag, properties, gameObject->transform->GetWorldScale().y, gameObject->transform->GetWorldScale().x) {}

BoxRigidBody::BoxRigidBody(GameObject* gameObject, const char* tag, bool isStatic, glm::vec2 velocity,
                           float rotationVelocity, float angularResistance, float linearResistance, bool gravityEnabled)
	: PhysicsBody(gameObject, tag, std::make_shared<Box>(0, 0),
	              TypeProperties(
		              RIGIDBODY, isStatic, velocity,
		              rotationVelocity,
		              angularResistance, linearResistance,
		              gravityEnabled)) {}

BoxRigidBody::BoxRigidBody(GameObject* gameObject, const char* tag, const TypeProperties& properties)
	: PhysicsBody(gameObject, tag, std::make_shared<Box>(0, 0),
	              TypeProperties(
		              RIGIDBODY, properties.isStatic, properties.velocity,
		              properties.rotationVelocity,
		              properties.angularResistance, properties.linearResistance,
		              properties.gravityEnabled)) {}
