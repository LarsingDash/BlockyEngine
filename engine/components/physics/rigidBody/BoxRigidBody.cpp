//
// Created by hmkam on 28/11/2024.
//

#include "BoxRigidBody.hpp"

#include "components/physics/shape/Shape.hpp"
#include "gameObject/GameObject.hpp"

BoxRigidBody::BoxRigidBody(GameObject* gameObject, const char* tag, bool isStatic, glm::vec2 velocity,
                           float rotationVelocity, float angularResistance, float linearResistance, bool gravityEnabled)
	: PhysicsBody(gameObject, tag, BOX,
	              TypeProperties(
		              RIGIDBODY,
		              isStatic,
		              velocity,
		              rotationVelocity,
		              angularResistance,
		              linearResistance,
		              gravityEnabled)) {}

BoxRigidBody::BoxRigidBody(GameObject* gameObject, const char* tag, const TypeProperties& properties)
	: PhysicsBody(gameObject, tag, BOX,
	              TypeProperties(
		              RIGIDBODY,
		              properties.isStatic,
		              properties.linearVelocity,
		              properties.rotationVelocity,
		              properties.rotationResistance,
		              properties.linearResistance,
		              properties.gravityEnabled)) {}
