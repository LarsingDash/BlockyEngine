#include "PhysicsModule.hpp"

#include <iostream>
#include <Box2D/Box2D.h>
#include "components/physics/shape/Shape.hpp"
#include <components/renderables/EllipseRenderable.hpp>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/WindowModule.hpp>

// objects scaled, based on GAME_SPEED so that it looks like the speed is incrementing,
//	since everything is GAME_SPEED closer to another and takes GAME_SPEED less time to move to same position.
// use SET_GAME_SPEED to change the GAME_SPEED.
float SET_GAME_SPEED = 1.1;
float GAME_SPEED = SET_GAME_SPEED;
float LAST_GAME_SPEED = GAME_SPEED;

PhysicsModule::PhysicsModule() {
	// Use lower gravity than 9.8 velocity so that objects do not face throw another.
	// Gravity value is starting velocity of gravity effected object not the terminal velocity,
	//	terminal velocity is still capped at 9.8
	b2Vec2 gravity(0.f, 0.98f);

	_box2dWorldObject = std::make_unique<b2World>(gravity);

	_contactListener = std::make_unique<MyContactListener>(&_physicsBodyToBodyMap);

	_box2dWorldObject->SetContactListener(_contactListener.get());
}

constexpr float physicsFPS = 60.0f;

void PhysicsModule::Update(float delta) {
	// FixedUpdate implementation/fix, since Box2D world Step is inconsistent at different fps
	static float totalDelta = 0;
	totalDelta += delta;

	bool updated = false;
	for (float fixedTimeStep = (1.f / physicsFPS); totalDelta >= fixedTimeStep; totalDelta -= fixedTimeStep) {
		if (updated) {
			if (_physicsBodyToBodyMap.empty()) { break; }

			auto pair = _physicsBodyToBodyMap.begin();
			auto root = pair->first->gameObject;
			while (root->parent != nullptr) { root = root->parent; }

			root->transform->RecalculateWorldMatrix();
		}
		updated = true;

		FixedUpdate(fixedTimeStep);
	}
}

void PhysicsModule::FixedUpdate(float delta) {
	// static int i = 0;
	// if (i >= 60) {
	// 	SET_GAME_SPEED += 0.1f;
	// 	i = 0;
	// }
	// i++;
	GAME_SPEED = SET_GAME_SPEED;

	_writingExternalInputToBox2DWorld();

	constexpr int32 positionIterations = 50; // high positionIterations > 50 result in bigger performers hit.
	constexpr int32 velocityIterations = 6; // high velocityIterations > 50 result in bigger performers hit.

	_box2dWorldObject->Step(delta, velocityIterations, positionIterations);

	_writingBox2DWorldToOutside();

	LAST_GAME_SPEED = GAME_SPEED;
}

void PhysicsModule::_updateBox2DIfChanges(const PhysicsBody* const physicsBody, Body* const body) {
	if (physicsBody == nullptr || body == nullptr) { return; }

	if (body->GetPosition() != _position(physicsBody) || body->GetAngle() != _rotation(physicsBody)) {
		body->b2body->SetTransform(_position(physicsBody), _rotation(physicsBody));
	}

	if (_linearVelocity(physicsBody) != body->PhysicsBodyLastLinearVelocity()) {
		body->b2body->SetLinearVelocity(body->PhysicsBodyLastLinearVelocity());
		body->PhysicsBodyLastLinearVelocity(_linearVelocity(physicsBody));
	}

	if (_rotationVelocity(physicsBody) != body->PhysicsBodyLastRotationVelocity()) {
		body->b2body->SetAngularVelocity(_rotationVelocity(physicsBody));
		body->PhysicsBodyLastRotationVelocity(_rotationVelocity(physicsBody));
	}

	if (_linearResistance(physicsBody) != body->PhysicsBodyLastLinearResistance()) {
		body->b2body->SetLinearDamping(_linearResistance(physicsBody));
		body->PhysicsBodyLastLinearResistance(_linearResistance(physicsBody));
	}
	if (_rotationResistance(physicsBody) != body->PhysicsBodyLastRotationResistance()) {
		body->b2body->SetAngularDamping(_rotationResistance(physicsBody));
		body->PhysicsBodyLastRotationResistance(_rotationResistance(physicsBody));
	}
}

void PhysicsModule::_writingExternalInputToBox2DWorld() {
	if (_physicsBodyToBodyMap.empty()) { return; }

	// recreate bodies if GAME_SPEED is changed, since GAME_SPEED is faked by resizing all object
	//	and multiplying position by resize, so it looks like GAME_SPEED increase or decrees
	if (GAME_SPEED != LAST_GAME_SPEED) {
		auto copy = _physicsBodyToBodyMap;
		for (auto [physicsBody, body] : copy) {
			if (body == nullptr || physicsBody == nullptr) { continue; }

			//todo: store properties to not lose velocity and other properties
			RemovePhysicsBody(*physicsBody);
			AddPhysicsBody(*physicsBody);

			_createPhysicsBody(*physicsBody);
		}
	}

	for (auto [physicsBody, body] : _physicsBodyToBodyMap) {
		if (body == nullptr && physicsBody == nullptr) { continue; }

		if (body == nullptr) {
			// create body hear, because sometimes when at AddBoxShape physicsBody.componentTransform->GetWorldScale() is still not set.
			_createPhysicsBody(*physicsBody);
			continue;
		}
		if (physicsBody != nullptr) {
			if (!body->_gameObjectIsInitialized) {
				// only need to initialize Position and Rotation, for gameObject transform, that needs deltaPosition
				body->LastPosition(_position(physicsBody));
				body->LastRotation(_rotation(physicsBody));

				body->PhysicsBodyLastLinearVelocity(_linearVelocity(physicsBody));
				body->PhysicsBodyLastRotationVelocity(_rotationVelocity(physicsBody));
				body->PhysicsBodyLastLinearResistance(_linearResistance(physicsBody));
				body->PhysicsBodyLastRotationResistance(_rotationResistance(physicsBody));

				body->SetTransform(
					_position(physicsBody),
					_rotation(physicsBody),
					_linearVelocity(physicsBody),
					_rotationVelocity(physicsBody),
					_linearResistance(physicsBody),
					_rotationResistance(physicsBody));

				body->_gameObjectIsInitialized = true;
			}

			_updateBox2DIfChanges(physicsBody, body);
		}
	}
}

void PhysicsModule::_writingBox2DWorldToOutside() {
	for (auto [physicsBody, body] : _physicsBodyToBodyMap) {
		if (body == nullptr || physicsBody == nullptr) { continue; }

		const b2Vec2 position = body->GetPosition();
		const b2Vec2 deltaPosition = {
			(position.x - body->LastPosition().x) * GAME_SPEED,
			(position.y - body->LastPosition().y) * GAME_SPEED
		};

		const float angle = body->GetAngle();
		const float deltaAngle = _toDegree(body->LastRotation() - angle);

		// Use gameObject to apply the movement to the whole gameObject
		if (deltaPosition != b2Vec2{0, 0}) {
			physicsBody->gameObject->transform->Translate(deltaPosition.x, deltaPosition.y);
		}
		if (deltaAngle != 0) { physicsBody->gameObject->transform->Rotate(deltaAngle); }

		body->LastPosition(position);
		body->LastRotation(angle);
	}
}

void PhysicsModule::AddPhysicsBody(PhysicsBody& physicsBody) {
	if (&physicsBody.gameObject == nullptr) {
		BLOCKY_ENGINE_ERROR("AddPhysicsBody but: physicsBody.gameObject == nullptr");
		return;
	}

	_physicsBodyToBodyMap[&physicsBody] = nullptr;
}

void PhysicsModule::_createPhysicsBody(PhysicsBody& physicsBody) {
	auto body = std::make_unique<Body>();
	body->b2body = _createBody(*_box2dWorldObject, physicsBody);

	_physicsBodyToBodyMap[&physicsBody] = body.get();
	_bodies.emplace_back(std::move(body));
}

void PhysicsModule::RemovePhysicsBody(PhysicsBody& physicsBody) {
	auto it = _physicsBodyToBodyMap.find(&physicsBody);
	if (it != _physicsBodyToBodyMap.end()) {
		// first erase form map, because when DestroyBody is called EndContact can be triggered, if body is removed when in contact.
		//	when erased from _physicsBodyToBodyMap EndContact cant find gameObject and EndContact handler of game objects is not called.
		if (it->second != nullptr) {
			const auto body = it->second->b2body;
			_physicsBodyToBodyMap.erase(it);
			_box2dWorldObject->DestroyBody(body);
		}
		else {
			_physicsBodyToBodyMap.erase(it);
		}
	}
}

std::unique_ptr<b2Shape> AddBoxShape(const PhysicsBody& physicsBody) {
	auto dynamicBox = std::make_unique<b2PolygonShape>();
	// Blocky Engine uses width and height, Box2D uses x&y height&width above,below&left,right of origin. so: /2
	dynamicBox->SetAsBox(physicsBody.componentTransform->GetWorldScale().x / 2 / GAME_SPEED,
	                     physicsBody.componentTransform->GetWorldScale().y / 2 / GAME_SPEED);

	return dynamicBox;
}

std::unique_ptr<b2Shape> AddCircleShape(const PhysicsBody& physicsBody) {
	auto dynamicCircle = std::make_unique<b2CircleShape>();
	dynamicCircle->m_radius = ((
		physicsBody.componentTransform->GetWorldScale().y +
		physicsBody.componentTransform->GetWorldScale().x) / 4) / GAME_SPEED;
	return dynamicCircle;
}

void PhysicsModule::_addFixture(PhysicsBody& physicsBody, b2Body* body) {
	b2FixtureDef fixtureDef;

	// if width/height/radius < 0, error: Assertion failed: area > 1.19209289550781250000000000000000000e-7F
	switch (physicsBody.GetShape()) {
		case BOX: {
			fixtureDef.shape = AddBoxShape(physicsBody).release();
			break;
		}
		case CIRCLE: {
			fixtureDef.shape = AddCircleShape(physicsBody).release();
			break;
		}
	}

	const auto& properties = physicsBody.ReadTypeProperties();
	switch (properties.physicsType) {
		case COLLIDER: {
			fixtureDef.isSensor = true;
			break;
		}
		case RIGIDBODY: {
			if (!properties.gravityEnabled) {
				body->SetGravityScale(0.0f);
			}
			else {
				body->SetGravityScale(1000.0f);
			}

			body->SetAngularDamping(_rotationResistance(&physicsBody));
			body->SetLinearDamping(_linearResistance(&physicsBody));

			body->SetAngularVelocity(_rotationVelocity(&physicsBody));
			body->SetLinearVelocity(_linearVelocity(&physicsBody));
			break;
		}
	}

	body->CreateFixture(&fixtureDef);

	// To have all objects apply the same force on another, the density attribute is not set, and all bodies are set to the same mass
	b2MassData b2_mass_data = {1.f};
	body->SetMassData(&b2_mass_data);

	delete fixtureDef.shape;
}

b2Body* PhysicsModule::_createBody(b2World& world, PhysicsBody& physicsBody) {
	// position and angel is not set when creating body, because physicsBody.gameObject position & angle is still default at this moment
	b2Body* body;

	auto pair = _physicsBodyToBodyMap.find(&physicsBody);

	// to have multiple PhysicsBodies on one game object use the same box2d body for the same game object.
	if (pair != _physicsBodyToBodyMap.end() && pair->second != nullptr && pair->second->b2body != nullptr) {
		body = pair->second->b2body;
	}
	else {
		b2BodyDef bodyDef;

		// when setting multiple different types of PhysicsBodies on the same gameObject will override partial properties
		const auto& properties = physicsBody.ReadTypeProperties();
		switch (properties.physicsType) {
			case COLLIDER: {
				bodyDef.type = b2_staticBody;
				break;
			}
			case RIGIDBODY: {
				if (properties.isStatic) {
					bodyDef.type = b2_kinematicBody;
					bodyDef.fixedRotation = true;
				}
				else {
					bodyDef.type = b2_dynamicBody;
					bodyDef.fixedRotation = false;
				}
				break;
			}
		}

		body = world.CreateBody(&bodyDef);
	}
	_addFixture(physicsBody, body);

	return body;
}

b2Vec2 PhysicsModule::_vecConvert(const glm::vec2& a) {
	return {a.x, a.y};
}

glm::vec2 PhysicsModule::_vecConvert(const b2Vec2& a) {
	return {a.x, a.y};
}

b2Vec2 PhysicsModule::_position(const PhysicsBody* physicsBody) {
	auto vec = _vecConvert(physicsBody->componentTransform->GetWorldPosition());
	vec.x /= GAME_SPEED;
	vec.y /= GAME_SPEED;
	return vec;
}

// Return rotation in radian
float PhysicsModule::_rotation(const PhysicsBody* physicsBody) {
	return _toRadian(physicsBody->componentTransform->GetWorldRotation());
}

// return Angel in degree
float PhysicsModule::_toDegree(float radian) {
	return (radian * (180.0f / static_cast<float>(M_PI)));
}

// Return rotation in radian
float PhysicsModule::_toRadian(float degree) {
	return (degree * (static_cast<float>(M_PI) / 180.0f));
}

b2Vec2 PhysicsModule::_linearVelocity(const PhysicsBody* physicsBody) {
	return _vecConvert(physicsBody->ReadTypeProperties().linearVelocity);
}

// return Angle in radian
float PhysicsModule::_rotationVelocity(const PhysicsBody* physicsBody) {
	return _toRadian(physicsBody->ReadTypeProperties().rotationVelocity);
}

float PhysicsModule::_rotationResistance(const PhysicsBody* physicsBody) {
	return physicsBody->ReadTypeProperties().rotationResistance;
}

float PhysicsModule::_linearResistance(const PhysicsBody* physicsBody) {
	return physicsBody->ReadTypeProperties().linearResistance;
}

