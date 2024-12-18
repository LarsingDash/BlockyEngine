#include "PhysicsModule.hpp"

#include <iostream>
#include <Box2D/Box2D.h>
#include <components/physics/shape/Box.hpp>
#include <components/physics/shape/Circle.hpp>
#include <components/renderables/EllipseRenderable.hpp>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>
#include <moduleManager/modules/WindowModule.hpp>

// objects scaled, based on DEBUG_GAME_SPEED so that it looks like the speed is incrementing,
//	since everything is DEBUG_GAME_SPEED closer to another and takes DEBUG_GAME_SPEED less time to move to same position.
constexpr float DEBUG_GAME_SPEED = 2;

PhysicsModule::PhysicsModule() {
	b2Vec2 gravity(0.f, 9.8f);

	_box2dWorldObject = std::make_unique<b2World>(gravity);

	_contactListener = std::make_unique<MyContactListener>(&_gameObjectToBodyMap);

	_box2dWorldObject->SetContactListener(_contactListener.get());
}

void PhysicsModule::Update(float delta) {
	// fixed update implementation/fix, since Box2D world Step is inconsistent at different fps
	static float totalDelta = 0;
	totalDelta += delta;
	constexpr float fixedTimeStep = (1.f / 60.f);
	while (totalDelta >= fixedTimeStep) {
		totalDelta -= fixedTimeStep;

		WritingExternalInputToBox2DWorld();

		constexpr int32 positionIterations = 2 * 100;
		constexpr int32 velocityIterations = 6; // high velocityIterations > 50 result in bigger performers hit.

		_box2dWorldObject->Step(fixedTimeStep, velocityIterations, positionIterations);

		WritingBox2DWorldToOutside();
	}
}

bool PhysicsModule::IsSame(const PhysicsBody* const physicsBody, const Body* const body) {
	if (physicsBody == nullptr || body == nullptr) { return false; }

	if (body->GetPosition() != Position(*physicsBody)) { return false; }
	if (body->GetAngle() != ToRadian(Angle(*physicsBody))) { return false; }

	if (body->GetLinearVelocity() != LinearVelocity(*physicsBody)) { return false; }
	if (body->GetRotationVelocity() != RotationVelocity(*physicsBody)) { return false; }

	if (body->GetLinearResistance() != LinearResistance(*physicsBody)) { return false; }
	if (body->GetAngularResistance() != RotationResistance(*physicsBody)) { return false; }

	return true;
}

void PhysicsModule::WritingExternalInputToBox2DWorld() {
	for (auto [physicsBody, body] : _gameObjectToBodyMap) {
		if (IsSame(physicsBody, body)) { continue; }

		if (!body->_gameObjectIsInitialized) {
			// only need to initialize Position and Rotation, for gameObject transform, that needs deltaPosition
			body->LastPosition(Position(*physicsBody));
			body->LastRotation(ToRadian(Angle(*physicsBody)));

			body->_gameObjectIsInitialized = true;
		}

		body->SetTransform(
			Position(*physicsBody),
			ToRadian(Angle(*physicsBody)),
			LinearVelocity(*physicsBody),
			RotationVelocity(*physicsBody),
			LinearResistance(*physicsBody),
			RotationResistance(*physicsBody));
	}
}

void PhysicsModule::WritingBox2DWorldToOutside() {
	for (auto [physicsBody, body] : _gameObjectToBodyMap) {
		const b2Vec2 position = body->GetPosition();
		const b2Vec2 deltaPosition = {
			(position.x - body->LastPosition().x) * DEBUG_GAME_SPEED,
			(position.y - body->LastPosition().y) * DEBUG_GAME_SPEED
		};

		const float angle = body->GetAngle();
		const float deltaAngle = body->LastRotation() - angle;

		// Use gameObject to apply the movement to the whole gameObject
		physicsBody->gameObject->transform->Translate(deltaPosition.x, deltaPosition.y);
		physicsBody->gameObject->transform->Rotate(ToDegree(deltaAngle));

		body->LastPosition({position.x, position.y});
		body->LastRotation(angle);
	}
}

void PhysicsModule::AddPhysicsBody(PhysicsBody& physicsBody) {
	if (&physicsBody.gameObject == nullptr) {
		BLOCKY_ENGINE_ERROR("AddPhysicsBody but: physicsBody.gameObject == nullptr");
		return;
	}

	auto body = std::make_unique<Body>();
	body->b2body = CreateBody(*_box2dWorldObject, physicsBody);

	_gameObjectToBodyMap[&physicsBody] = body.get();
	_bodies.emplace_back(std::move(body));
}

void PhysicsModule::RemovePhysicsBody(PhysicsBody& physicsBody) {
	auto it = _gameObjectToBodyMap.find(&physicsBody);
	if (it != _gameObjectToBodyMap.end()) {
		// first erase form map, because when DestroyBody is called EndContact can be triggered, if body is removed when in contact.
		//	when erased from _gameObjectToBodyMap EndContact cant find gameObject and EndContact handler of game objects is not called.
		const auto body = it->second->b2body;
		_gameObjectToBodyMap.erase(it);
		_box2dWorldObject->DestroyBody(body);
	}
}

std::unique_ptr<b2Shape> AddBoxShape(const Box& box) {
	auto dynamicBox = std::make_unique<b2PolygonShape>();
	// Blocky Engine uses width and height, Box2D uses x&y height&width above,below&left,right of origin. so: /2
	dynamicBox->SetAsBox(box.GetWidth() / 2 / DEBUG_GAME_SPEED,
	                     box.GetHeight() / 2 / DEBUG_GAME_SPEED);

	return dynamicBox;
}

std::unique_ptr<b2Shape> AddCircleShape(const Circle& circle) {
	auto dynamicCircle = std::make_unique<b2CircleShape>();
	dynamicCircle->m_radius = circle.GetRadius() / DEBUG_GAME_SPEED;
	return dynamicCircle;
}

void PhysicsModule::AddFixture(PhysicsBody& physicsBody, b2Body* body) {
	b2FixtureDef fixtureDef;

	// if width/height/radius < 0, error: Assertion failed: area > 1.19209289550781250000000000000000000e-7F
	switch (physicsBody.GetShape()) {
		case BOX: {
			const auto* const shape = dynamic_cast<Box*>(physicsBody.GetShapeReference().get());
			fixtureDef.shape = AddBoxShape(*shape).release();
			break;
		}
		case CIRCLE: {
			const auto* const shape = dynamic_cast<Circle*>(physicsBody.GetShapeReference().get());
			fixtureDef.shape = AddCircleShape(*shape).release();
			break;
		}
	}

	auto properties = physicsBody.GetTypeProperties();
	switch (properties->physicsType) {
		case COLLIDER: {
			fixtureDef.isSensor = true;
			break;
		}
		case RIGIDBODY: {
			if (!properties->gravityEnabled) {
				body->SetGravityScale(0.0f);
			}
			else {
				body->SetGravityScale(1000.0f);
			}

			body->SetAngularDamping(RotationResistance(physicsBody));
			body->SetLinearDamping(LinearResistance(physicsBody));

			body->SetAngularVelocity(ToRadian(RotationVelocity(physicsBody)));
			body->SetLinearVelocity(LinearVelocity(physicsBody));
			break;
		}
	}

	body->CreateFixture(&fixtureDef);

	// To have all objects apply the same force on another, the density attribute is not set, and all bodies are set to the same mass
	b2MassData b2_mass_data = {0.1f};
	body->SetMassData(&b2_mass_data);

	delete fixtureDef.shape;
}

b2Body* PhysicsModule::CreateBody(b2World& world, PhysicsBody& physicsBody) {
	// position and angel is not set when creating body, because physicsBody.gameObject position & angle is still default at this moment
	b2Body* body;

	auto pair = _gameObjectToBodyMap.find(&physicsBody);

	// to have multiple PhysicsBodies on one game object use the same box2d body for the same game object.
	if (pair != _gameObjectToBodyMap.end()) {
		body = pair->second->b2body;
	}
	else {
		b2BodyDef bodyDef;

		// when setting multiple different types of PhysicsBodies on the same gameObject will override partial properties
		auto properties = physicsBody.GetTypeProperties();
		switch (properties->physicsType) {
			case COLLIDER: {
				bodyDef.type = b2_staticBody;
				break;
			}
			case RIGIDBODY: {
				if (properties->isStatic) {
					bodyDef.type = b2_kinematicBody;
				}
				else {
					bodyDef.type = b2_dynamicBody;
				}
				break;
			}
		}

		body = world.CreateBody(&bodyDef);
	}

	AddFixture(physicsBody, body);

	return body;
}

b2Vec2 PhysicsModule::VecConvert(const glm::vec2& a) {
	return {a.x, a.y};
}

glm::vec2 PhysicsModule::VecConvert(const b2Vec2& a) {
	return {a.x, a.y};
}

b2Vec2 PhysicsModule::Position(const PhysicsBody& physicsBody) {
	auto vec = VecConvert(physicsBody.componentTransform->GetWorldPosition());
	vec.x /= DEBUG_GAME_SPEED;
	vec.y /= DEBUG_GAME_SPEED;
	return vec;
}

b2Vec2 PhysicsModule::LinearVelocity(const PhysicsBody& physicsBody) {
	return VecConvert(physicsBody.GetTypeProperties().linearVelocity);
}

float PhysicsModule::RotationVelocity(const PhysicsBody& physicsBody) {
	return physicsBody.GetTypeProperties().rotationVelocity;
}

float PhysicsModule::RotationResistance(const PhysicsBody& physicsBody) {
	return physicsBody.GetTypeProperties().rotationResistance;
}

float PhysicsModule::LinearResistance(const PhysicsBody& physicsBody) {
	return physicsBody.GetTypeProperties().linearResistance;
}

float PhysicsModule::ToDegree(float radian) {
	return (radian * (180.0f / static_cast<float>(M_PI)));
}

float PhysicsModule::ToRadian(float degree) {
	return (degree * (static_cast<float>(M_PI) / 180.0f));
}

float PhysicsModule::Angle(const PhysicsBody& physicsBody) {
	return physicsBody.componentTransform->GetWorldRotation();
}

