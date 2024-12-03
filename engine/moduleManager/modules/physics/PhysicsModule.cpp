#include "PhysicsModule.hpp"
#include <Box2D/Box2D.h>
#include <components/physics/shape/Box.hpp>
#include <components/physics/shape/Circle.hpp>
#include <components/renderables/EllipseRenderable.hpp>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

PhysicsModule::PhysicsModule() {
	b2Vec2 gravity(0.f, 9.8f);

	_box2dWorldObject = std::make_unique<b2World>(gravity);

	_contactListener = std::make_unique<MyContactListener>(&_gameObjectToBodyMap);

	_box2dWorldObject->SetContactListener(_contactListener.get());
}

void PhysicsModule::Update(float delta) {
	WritingExternalInputToBox2DWorld();

	constexpr int32 positionIterations = 2;
	constexpr int32 velocityIterations = 6;

	_box2dWorldObject->Step(delta, velocityIterations, positionIterations);

	WritingBox2DWorldToOutside();
}

bool PhysicsModule::IsSame(const GameObject* const gameObject, const Body* const body) {
	if (gameObject == nullptr || body == nullptr) { return false; }

	if (body->GetPosition() != Position(*gameObject)) { return false; }

	if (body->GetAngle() != Angle(*gameObject)) { return false; }

	return true;
}

void PhysicsModule::WritingExternalInputToBox2DWorld() {
	for (auto [gameObject, body] : _gameObjectToBodyMap) {
		if (IsSame(gameObject, body)) { continue; }
		if (!body->_gameObjectIsInitialized) {
			body->LastPosition(Position(*gameObject));
			body->LastRotation(Angle(*gameObject));
			body->_gameObjectIsInitialized = true;
		}

		body->b2body->SetTransform(Position(*gameObject), Angle(*gameObject));
	}
}

void PhysicsModule::WritingBox2DWorldToOutside() {
	for (auto [gameObject, body] : _gameObjectToBodyMap) {
		const b2Vec2 position = body->GetPosition();
		const b2Vec2 deltaPosition = {
			position.x - body->LastPosition().x, position.y - body->LastPosition().y
		};

		const auto scale = gameObject->transform->GetWorldScale();

		const float angle = body->GetAngle();
		const float deltaAngle = body->LastRotation() - angle;

		gameObject->transform->Translate(deltaPosition.x / scale.x, deltaPosition.y / scale.y);
		gameObject->transform->Rotate(deltaAngle);

		body->LastPosition({position.x, position.y});
		body->LastRotation(angle);
	}
}

void PhysicsModule::AddCollider(PhysicsBody& physicsBody) {
	if (&physicsBody.gameObject == nullptr) {
		BLOCKY_ENGINE_ERROR("AddCollider but: physicsBody.gameObject == nullptr");
		return;
	}

	auto body = std::make_unique<Body>();
	body->b2body = CreateBody(*_box2dWorldObject, physicsBody);

	_gameObjectToBodyMap[&physicsBody.gameObject] = body.get();
	_bodies.emplace_back(std::move(body));
}

void PhysicsModule::RemoveCollider(const PhysicsBody& physicsBody) {
	auto it = _gameObjectToBodyMap.find(&physicsBody.gameObject);
	if (it != _gameObjectToBodyMap.end()) {
		_box2dWorldObject->DestroyBody(it->second->b2body);
		_gameObjectToBodyMap.erase(it);
	}
}

std::unique_ptr<b2Shape> AddBoxShape(const Box& collider) {
	auto dynamicBox = std::make_unique<b2PolygonShape>();
	// Blocky Engine uses width and height, Box2D uses x&y height&width above,below&left,right of origin. so: /2
	dynamicBox->SetAsBox(collider.GetWidth() / 2, collider.GetHeight() / 2);

	return dynamicBox;
}

std::unique_ptr<b2Shape> AddCircleShape(const Circle& collider) {
	auto dynamicCircle = std::make_unique<b2CircleShape>();
	dynamicCircle->m_radius = collider.GetRadius();
	return dynamicCircle;
}

void PhysicsModule::AddFixture(PhysicsBody& physicsBody, b2Body* body) {
	b2FixtureDef fixtureDef;

	// if width/height/radius < 0, error: Assertion failed: area > 1.19209289550781250000000000000000000e-7F
	switch (physicsBody.GetShape()) {
		case BOX: {
			const auto* const shape = dynamic_cast<Box*>(physicsBody.GetShapeReference()->get());
			fixtureDef.shape = AddBoxShape(*shape).release();
			break;
		}
		case CIRCLE: {
			const auto* const shape = dynamic_cast<Circle*>(physicsBody.GetShapeReference()->get());
			fixtureDef.shape = AddCircleShape(*shape).release();
			break;
		}
	}

	switch (physicsBody.GetTypeProperties().physicsType) {
		case COLLIDER: {
			fixtureDef.isSensor = true;
			break;
		}
		case RIGIDBODY: {
			if (!physicsBody.GetTypeProperties().gravityEnabled) {
				body->SetGravityScale(0.0f);
			}

			body->SetAngularDamping(physicsBody.GetTypeProperties().angularResistance);
			body->SetLinearDamping(physicsBody.GetTypeProperties().linearResistance);

			body->SetFixedRotation(false);
			body->SetAngularVelocity(physicsBody.GetTypeProperties().rotationVelocity);
			body->SetLinearVelocity(VecConvert(physicsBody.GetTypeProperties().velocity));
			break;
		}
	}

	body->CreateFixture(&fixtureDef);

	// To have all objects apply the same force on another, the density attribute is not set, and all bodies are set to the same mass
	b2MassData b2_mass_data = {1.f};
	body->SetMassData(&b2_mass_data);

	delete fixtureDef.shape;
}

b2Body* PhysicsModule::CreateBody(b2World& world, PhysicsBody& physicsBody) {
	// position and angel is not set when creating body, because physicsBody.gameObject position & angle is still default at this moment
	b2Body* body;

	auto gameObject = _gameObjectToBodyMap.find(&physicsBody.gameObject);

	// to have multiple PhysicsBodies on one game object use the same box2d body for the same game object.
	if (gameObject != _gameObjectToBodyMap.end()) {
		body = gameObject->second->b2body;
	}
	else {
		b2BodyDef bodyDef;

		// when setting multiple different types of PhysicsBodies on the same gameObject will override partial properties
		switch (physicsBody.GetTypeProperties().physicsType) {
			case COLLIDER: {
				bodyDef.type = b2_staticBody;
				break;
			}
			case RIGIDBODY: {
				if (physicsBody.GetTypeProperties().isStatic) {
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
	return VecConvert(physicsBody.componentTransform->GetWorldPosition());
}

b2Vec2 PhysicsModule::Position(const GameObject& gameObject) {
	return VecConvert(gameObject.transform->GetWorldPosition());
}

float PhysicsModule::Angle(const PhysicsBody& physicsBody) {
	return physicsBody.componentTransform->GetWorldRotation();
}

float PhysicsModule::Angle(const GameObject& gameObject) {
	return gameObject.transform->GetWorldRotation();
}

