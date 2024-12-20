//
// Created by hmkam on 28/11/2024.
//

#include "CircleRigidBody.hpp"

#include <components/physics/shape/Circle.hpp>
#include <gameObject/GameObject.hpp>

CircleRigidBody::CircleRigidBody(GameObject* gameObject, const char* tag, bool isStatic, glm::vec2 velocity,
                                 float rotationVelocity, float angularResistance, float linearResistance,
                                 bool gravityEnabled) : CircleRigidBody(gameObject, tag, isStatic, velocity,
                                                                        rotationVelocity,
                                                                        angularResistance, linearResistance,
                                                                        gravityEnabled,
                                                                        (gameObject->transform->GetLocalScale().y +
	                                                                        gameObject->transform->
	                                                                        GetLocalScale().x) / 4) {}

CircleRigidBody::CircleRigidBody(GameObject* gameObject, const char* tag, const TypeProperties& properties):
	CircleRigidBody(gameObject, tag, properties,
	                (gameObject->transform->GetLocalScale().y + gameObject->transform->GetLocalScale().x) / 4) {}

CircleRigidBody::CircleRigidBody(GameObject* gameObject, const char* tag, bool isStatic,
                                 glm::vec2 velocity,
                                 float rotationVelocity, float angularResistance, float linearResistance,
                                 bool gravityEnabled,
                                 float radius) : PhysicsBody(gameObject, tag,
                                                             std::make_shared<Circle>(radius),
                                                             TypeProperties(
	                                                             RIGIDBODY, isStatic, velocity,
	                                                             rotationVelocity,
	                                                             angularResistance, linearResistance,
	                                                             gravityEnabled)) {}

CircleRigidBody::CircleRigidBody(GameObject* gameObject, const char* tag, const TypeProperties& properties,
                                 float radius) : PhysicsBody(gameObject, tag,
                                                             std::make_shared<Circle>(radius),
                                                             TypeProperties(
	                                                             RIGIDBODY, properties.isStatic,
	                                                             properties.velocity,
	                                                             properties.rotationVelocity,
	                                                             properties.angularResistance,
	                                                             properties.linearResistance,
	                                                             properties.gravityEnabled)) {}
