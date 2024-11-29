#include "PhysicsModule.hpp"
#include <Box2D/Box2D.h>
#include <components/physics/shape/Box.hpp>
#include <components/physics/shape/Circle.hpp>
#include <components/renderables/EllipseRenderable.hpp>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

//todo: fix multiple rigid bodys on same gameobject, so that they can overlap
PhysicsModule::PhysicsModule() {
	b2Vec2 gravity(0.f, 9.8f);
	// b2Vec2 gravity(0.f, 0.f);

	_box2dWorldObject = std::make_unique<b2World>(gravity);

	_contactListener = std::make_unique<MyContactListener>(&_colliderToBodyMap);

	_box2dWorldObject->SetContactListener(_contactListener.get());
}

void PhysicsModule::Update(float delta) {
	WritingExternalInputToBox2DWorld();

	constexpr int32 positionIterations = 2 * 1000;
	constexpr int32 velocityIterations = 6 * 1000;

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

		// BLOCKY_ENGINE_DEBUG_STREAM("diff: ")
		// // BLOCKY_ENGINE_DEBUG(VecConvert(Position(*collider)))
		// BLOCKY_ENGINE_DEBUG((collider->componentTransform->GetWorldPosition()))
		// BLOCKY_ENGINE_DEBUG((collider->gameObject.transform->GetWorldPosition()))
		// BLOCKY_ENGINE_DEBUG((collider->componentTransform->GetLocalPosition()))
		// BLOCKY_ENGINE_DEBUG((collider->gameObject.transform->GetLocalPosition()))
		// BLOCKY_ENGINE_DEBUG(VecConvert(body->GetPosition()))

		body->SetTransform(Position(*collider), Angle(*collider));

		// Destroy all existing fixtures so if there is a resize the resize can be applied
		for (b2Fixture* fixture = body->GetFixtureList(); fixture;) {
			b2Fixture* next = fixture->GetNext();
			body->DestroyFixture(fixture);
			fixture = next;
		}

		AddFixture(*collider, body);
	}
}

void PhysicsModule::WritingBox2DWorldToOutside() {
	for (auto [collider, body] : _colliderToBodyMap) {
		b2Vec2 pos = body->GetPosition();
		b2Vec2 d = {pos.x - collider->lastPos.x, pos.y - collider->lastPos.y};

		float deltaAngle = body->GetAngle() - collider->lastRotation;
		const auto scale = collider->gameObject.transform->GetWorldScale();
		//todo: fix this for first setup after init all is 0 and -> 400
		if (abs(d.x) <= 100 && abs(d.y) <= 100) {
			// todo: uitleg GetWorldScale is to small and generates runaway if to large
			collider->gameObject.transform->Translate(d.x / scale.x / 2, d.y / scale.y / 2);
			collider->gameObject.transform->Rotate(deltaAngle);
		}

		// BLOCKY_ENGINE_DEBUG(collider->gameObject.tag);
		// auto goPos = collider->gameObject.transform->GetWorldPosition();
		// auto coPos = collider->componentTransform->GetWorldPosition();
		// BLOCKY_ENGINE_DEBUG_STREAM("pos  \t" << pos.x << " ; " << pos.y);
		// BLOCKY_ENGINE_DEBUG_STREAM("gopos\t" << goPos.x << " ; " << goPos.y);
		// BLOCKY_ENGINE_DEBUG_STREAM("coPos\t" << coPos.x << " ; " << coPos.y);
		// BLOCKY_ENGINE_DEBUG_STREAM("last \t" << collider->lastPos.x << " ; " << collider->lastPos.y);
		// BLOCKY_ENGINE_DEBUG_STREAM("dx dy\t" << d.x<< " ; " << d.y)
		// BLOCKY_ENGINE_DEBUG_STREAM("scale\t" << scale.x << " ; " << scale.y);

		collider->lastPos = glm::vec2{pos.x, pos.y};
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
	// Define another box shape for the first dynamic body.
	auto dynamicBox = std::make_unique<b2PolygonShape>();
	// Blocky Engine uses width and height, Box2D uses x&y height&width above,below&left,right of origin. so: /2
	dynamicBox->SetAsBox(collider.GetWidth() / 2, collider.GetHeight() / 2);

	// BLOCKY_ENGINE_DEBUG_STREAM("AddBoxShape: "<<collider.GetWidth() << ";" << collider.GetHeight());
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
	switch (collider.GetType()) {
		case BOX: {
			const auto* const shape = dynamic_cast<Box*>(collider.physicsShape.get());
			fixtureDef.shape = AddBoxShape(*shape).release();
			break;
		}
		case CIRCLE: {
			const auto* const shape = dynamic_cast<Circle*>(collider.physicsShape.get());
			fixtureDef.shape = AddCircleShape(*shape).release();
			break;
		}
	}

	// set all object to static, and later overwrite the mass if object is not static
	constexpr float staticObject = 0.0f;
	fixtureDef.density = staticObject;

	body->CreateFixture(&fixtureDef);

	if (!collider.physicsShape->isStatic) {
		// to have all non-static object apply the same force on another, set all bodies to mass 1
		b2MassData mass = {0.f};
		body->SetMassData(&mass);
	}

	delete fixtureDef.shape;
}

b2Body* PhysicsModule::CreateBody(b2World& world, PhysicsBody& collider) {
	auto [x,y] = Position(collider);
	auto angle = Angle(collider);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.angle = angle;
	b2Body* body = world.CreateBody(&bodyDef);

	AddFixture(collider, body);

	// BLOCKY_ENGINE_DEBUG_STREAM("CreateBody: x: " << x << ", y: " << y << ", angle: " << angle);

	return body;
}

b2Vec2 PhysicsModule::VecConvert(const glm::vec2& a) {
	return {a.x, a.y};
}

glm::vec2 PhysicsModule::VecConvert(const b2Vec2& a) {
	return {a.x, a.y};
}

b2Vec2 PhysicsModule::Position(const PhysicsBody& collider) {
	//todo: add gameObject transforms
	// return VecConvert(collider.gameObject.transform->GetWorldPosition());
	return VecConvert(collider.componentTransform->GetWorldPosition());
	// return VecConvert(collider.componentTransform->GetLocalPosition());
}

float PhysicsModule::Angle(const PhysicsBody& collider) {
	//todo: add gameObject transforms
	// return collider.gameObject.transform->GetWorldRotation();
	return collider.componentTransform->GetWorldRotation();
	// return collider.componentTransform->GetLocalRotation();
}

