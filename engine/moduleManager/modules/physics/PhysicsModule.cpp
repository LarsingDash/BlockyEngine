#include "PhysicsModule.hpp"
#include <Box2D/Box2D.h>
#include <components/physics/shape/Box.hpp>
#include <components/physics/shape/Circle.hpp>
#include <components/renderables/EllipseRenderable.hpp>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

//todo: angle not working everywhere
//todo: fix multiple rigid bodys on same gameobject, so that they can overlap
//todo: speedup simmulation
PhysicsModule::PhysicsModule() {
	b2Vec2 gravity(0.f, 9.8f);

	_box2dWorldObject = std::make_unique<b2World>(gravity);

	_contactListener = std::make_unique<MyContactListener>(&_colliderToBodyMap);

	_box2dWorldObject->SetContactListener(_contactListener.get());
}

void PhysicsModule::Update(float delta) {
	WritingExternalInputToBox2DWorld();

	constexpr int32 positionIterations = 2;
	constexpr int32 velocityIterations = 6;

	_box2dWorldObject->Step(delta, velocityIterations, positionIterations);

	WritingBox2DWorldToOutside();
}

bool PhysicsModule::IsSame(const PhysicsBody* const collider, const b2Body* const body) {
	if (collider == nullptr || body == nullptr) { return false; }

	if (body->GetPosition() != Position(*collider)) { return false; }

	if (body->GetAngle() != Angle(*collider)) { return false; }

	return true;
}

void PhysicsModule::WritingExternalInputToBox2DWorld() {
	for (auto [collider, body] : _colliderToBodyMap) {
		if (IsSame(collider, body)) { continue; }

		BLOCKY_ENGINE_DEBUG_STREAM("diff: ")
		// BLOCKY_ENGINE_DEBUG(VecConvert(Position(*collider)))
		BLOCKY_ENGINE_DEBUG((collider->componentTransform->GetWorldPosition()))
		BLOCKY_ENGINE_DEBUG((collider->gameObject.transform->GetWorldPosition()))
		BLOCKY_ENGINE_DEBUG((collider->componentTransform->GetLocalPosition()))
		BLOCKY_ENGINE_DEBUG((collider->gameObject.transform->GetLocalPosition()))
		BLOCKY_ENGINE_DEBUG(VecConvert(body->GetPosition()))

		body->SetTransform(Position(*collider), Angle(*collider));

		// Destroy all existing fixtures so if there is a resize the resize can be applied
		for (b2Fixture* fixture = body->GetFixtureList(); fixture;) {
			b2Fixture* next = fixture->GetNext();
			body->DestroyFixture(fixture);
			fixture = next;
		}

		AddFixture(*collider, body);

		if (!collider->InitDone()) {
			collider->LastPosition(VecConvert(Position(*collider)));
			collider->LastRotation(Angle(*collider));
		}
	}
}

void PhysicsModule::WritingBox2DWorldToOutside() {
	for (auto [collider, body] : _colliderToBodyMap) {
		b2Vec2 position = body->GetPosition();
		b2Vec2 deltaPosition = {position.x - collider->LastPosition().x, position.y - collider->LastPosition().y};

		const auto scale = collider->gameObject.transform->GetWorldScale();

		float angle = body->GetAngle();
		float deltaAngle = angle - collider->LastRotation();

		// todo: uitleg GetWorldScale is to small and generates runaway if to large
		collider->gameObject.transform->Translate(deltaPosition.x / scale.x / 2, deltaPosition.y / scale.y / 2);
		collider->gameObject.transform->Rotate(deltaAngle / 2);

		std::cout << "GetWorldRotation: " << (collider->gameObject.transform->GetWorldRotation()) << std::endl;
		std::cout << "GetLocalRotation: " << (collider->gameObject.transform->GetLocalRotation()) << std::endl;
		std::cout << "deltaAngle: " << (deltaAngle) << std::endl;
		std::cout << "angle: " << (angle) << std::endl;

		collider->LastPosition(glm::vec2{position.x, position.y});
		collider->LastRotation(angle);
	}
}

void PhysicsModule::AddCollider(PhysicsBody& collider) {
	BLOCKY_ENGINE_DEBUG_STREAM("AddCollider: "<<collider.tag)
	b2Body* body = CreateBody(*_box2dWorldObject, collider);

	_colliderToBodyMap[&collider] = body;
}

void PhysicsModule::RemoveCollider(PhysicsBody& collider) {
	auto it = _colliderToBodyMap.find(&collider);
	if (it != _colliderToBodyMap.end()) {
		_box2dWorldObject->DestroyBody(it->second);
		_colliderToBodyMap.erase(it);
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

			std::cout << Angle(collider) << std::endl;

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

b2Body* PhysicsModule::CreateBody(b2World& world, PhysicsBody& collider) {
	auto [x,y] = Position(collider);
	auto angle = Angle(collider);

	b2BodyDef bodyDef;

	switch (collider.GetTypeProperties().physicsType) {
		case COLLIDER: {
			bodyDef.type = b2_kinematicBody;
			break;
		}
		case RIGIDBODY: {
			bodyDef.type = b2_dynamicBody;
			break;
		}
	}

	if (collider.GetTypeProperties().isStatic) {
		bodyDef.type = b2_staticBody;
	}

	bodyDef.position.Set(x, y);
	bodyDef.angle = angle;
	b2Body* body = world.CreateBody(&bodyDef);

	AddFixture(collider, body);

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

