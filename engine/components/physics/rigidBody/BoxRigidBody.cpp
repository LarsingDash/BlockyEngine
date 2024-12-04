//
// Created by hmkam on 28/11/2024.
//

#include "BoxRigidBody.hpp"

#include <components/physics/shape/Box.hpp>

BoxRigidBody::BoxRigidBody(GameObject& gameObject, const char* tag, bool isStatic, glm::vec2 velocity,
                           float rotationVelocity, float angularResistance, float linearResistance, bool gravityEnabled,
                           float height,
                           float width) : PhysicsBody(gameObject, tag,
                                                      std::make_unique<Box>(height, width),
                                                      TypeProperties(
	                                                      RIGIDBODY, isStatic, velocity,
	                                                      rotationVelocity,
	                                                      angularResistance, linearResistance,
	                                                      gravityEnabled)) {}

BoxRigidBody::BoxRigidBody(GameObject& gameObject, const char* tag, const TypeProperties& properties,
                           float height,
                           float width) : PhysicsBody(gameObject, tag,
                                                      std::make_unique<Box>(height, width),
                                                      TypeProperties(
	                                                      RIGIDBODY, properties.isStatic, properties.velocity,
	                                                      properties.rotationVelocity,
	                                                      properties.angularResistance, properties.linearResistance,
	                                                      properties.gravityEnabled)) {}
