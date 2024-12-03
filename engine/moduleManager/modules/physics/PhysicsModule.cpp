#include "PhysicsModule.hpp"
#include <Box2D/Box2D.h>
#include <components/physics/shape/Box.hpp>
#include <components/physics/shape/Circle.hpp>
#include <components/renderables/EllipseRenderable.hpp>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

//todo: fix multiple rigid bodys on same gameobject, so that they can overlap
//todo: speedup simmulation
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

bool PhysicsModule::IsSame(const PhysicsBody* const physicsBody, const b2Body* const body) {
	if (physicsBody == nullptr || body == nullptr) { return false; }

	if (body->GetPosition() != Position(*physicsBody)) { return false; }

	if (body->GetAngle() != Angle(*physicsBody)) { return false; }

	return true;
}

void PhysicsModule::WritingExternalInputToBox2DWorld() {
	for (auto [gameObject, body] : _gameObjectToBodyMap) {
		//todo: multie?
		const auto physicsBody = gameObject->GetComponent<PhysicsBody>();
		if (physicsBody == nullptr) {
			continue; //todo: GetComponent
		}

		if (IsSame(physicsBody, body)) { continue; }

		// BLOCKY_ENGINE_DEBUG_STREAM("diff: ")
		// // BLOCKY_ENGINE_DEBUG(VecConvert(Position(*collider)))
		// BLOCKY_ENGINE_DEBUG((physicsBody->componentTransform->GetWorldPosition()))
		// BLOCKY_ENGINE_DEBUG((physicsBody->gameObject.transform->GetWorldPosition()))
		// BLOCKY_ENGINE_DEBUG((physicsBody->componentTransform->GetLocalPosition()))
		// BLOCKY_ENGINE_DEBUG((physicsBody->gameObject.transform->GetLocalPosition()))
		// BLOCKY_ENGINE_DEBUG(VecConvert(body->GetPosition()))

		body->SetTransform(Position(*physicsBody), Angle(*physicsBody));

		//todo:
		// // Destroy all existing fixtures so if there is a resize the resize can be applied
		// for (b2Fixture* fixture = body->GetFixtureList(); fixture;) {
		// 	b2Fixture* next = fixture->GetNext();
		// 	body->DestroyFixture(fixture);
		// 	fixture = next;
		// }
		//
		// AddFixture(*collider, body);

		if (!physicsBody->InitDone()) {
			physicsBody->LastPosition(VecConvert(Position(*physicsBody)));
			physicsBody->LastRotation(Angle(*physicsBody));
		}
	}
}

void PhysicsModule::WritingBox2DWorldToOutside() {
	for (auto [gameObject, body] : _gameObjectToBodyMap) {
		//todo: multie?
		const auto physicsBody = gameObject->GetComponent<PhysicsBody>();
		if (physicsBody == nullptr) {
			continue; //todo: GetComponent
		}

		const b2Vec2 position = body->GetPosition();
		const b2Vec2 deltaPosition = {
			position.x - physicsBody->LastPosition().x, position.y - physicsBody->LastPosition().y
		};

		const auto scale = physicsBody->gameObject.transform->GetWorldScale();

		const float angle = body->GetAngle();
		const float deltaAngle = angle - physicsBody->LastRotation();

		// todo: uitleg GetWorldScale is to small and generates runaway if to large
		physicsBody->gameObject.transform->Translate(deltaPosition.x / scale.x / 2, deltaPosition.y / scale.y / 2);
		physicsBody->gameObject.transform->Rotate(deltaAngle / 2);

		physicsBody->LastPosition(glm::vec2{position.x, position.y});
		physicsBody->LastRotation(angle);
	}
}

void PhysicsModule::AddCollider(PhysicsBody& physicsBody) {
	BLOCKY_ENGINE_DEBUG_STREAM("AddCollider: "<<physicsBody.tag)
	b2Body* body = CreateBody(*_box2dWorldObject, physicsBody);

	if (&physicsBody.gameObject == nullptr) {
		return;
	}
	_gameObjectToBodyMap[&physicsBody.gameObject] = body;
}

void PhysicsModule::RemoveCollider(const PhysicsBody& physicsBody) {
	auto it = _gameObjectToBodyMap.find(&physicsBody.gameObject); //todo & to *
	if (it != _gameObjectToBodyMap.end()) {
		_box2dWorldObject->DestroyBody(it->second);
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

void PhysicsModule::AddFixture(PhysicsBody& collider, b2Body* body) {
	b2FixtureDef fixtureDef;

	// if width/height/radius < 0, error: Assertion failed: area > 1.19209289550781250000000000000000000e-7F
	switch (collider.GetShape()) {
		case BOX: {
			const auto* const shape = dynamic_cast<Box*>(collider.GetShapeReference()->get());
			fixtureDef.shape = AddBoxShape(*shape).release();
			break;
		}
		case CIRCLE: {
			const auto* const shape = dynamic_cast<Circle*>(collider.GetShapeReference()->get());
			fixtureDef.shape = AddCircleShape(*shape).release();
			break;
		}
	}

	switch (collider.GetTypeProperties().physicsType) {
		case COLLIDER: {
			body->SetGravityScale(0.0f);
			fixtureDef.isSensor = true;
			break;
		}
		case RIGIDBODY: {
			if (!collider.GetTypeProperties().gravityEnabled) {
				body->SetGravityScale(0.0f);
			}

			body->SetAngularDamping(collider.GetTypeProperties().angularResistance);
			body->SetLinearDamping(collider.GetTypeProperties().linearResistance);

			body->SetFixedRotation(false);
			body->SetAngularVelocity(collider.GetTypeProperties().rotationVelocity);
			body->ApplyForceToCenter(VecConvert(collider.GetTypeProperties().velocity), true);
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
	auto [x,y] = Position(physicsBody);
	auto angle = Angle(physicsBody);
	b2Body* body;

	auto gameObject = _gameObjectToBodyMap.find(&physicsBody.gameObject);

	// to have multiple PhysicsBodys on one game object use the same box2d body for the same game object.
	if (gameObject != _gameObjectToBodyMap.end()) {
		body = gameObject->second;
	}
	else {
		b2BodyDef bodyDef;

		//todo: not working now?
		switch (physicsBody.GetTypeProperties().physicsType) {
			case COLLIDER: {
				bodyDef.type = b2_kinematicBody;
				break;
			}
			case RIGIDBODY: {
				bodyDef.type = b2_dynamicBody;
				break;
			}
		}

		if (physicsBody.GetTypeProperties().isStatic) {
			bodyDef.type = b2_staticBody;
		}

		bodyDef.position.Set(x, y);
		bodyDef.angle = angle;
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

b2Vec2 PhysicsModule::Position(const PhysicsBody& collider) {
	return VecConvert(collider.componentTransform->GetWorldPosition());
}

float PhysicsModule::Angle(const PhysicsBody& collider) {
	return collider.componentTransform->GetWorldRotation();
}

