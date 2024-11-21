#include "PhysicsModule.hpp"

#include <Box2D/Box2D.h>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

PhysicsModule::PhysicsModule()
{
	//todo: Create a new Box2D world gravity not needed yet
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 0.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	_box2dWorldObject = new b2World(gravity);
}

PhysicsModule::~PhysicsModule()
{
	delete _box2dWorldObject;
}

void PhysicsModule::Update(float delta)
{
	// todo: writing external input in box2d world
	for (auto pair : _colliderToBodyMap)
	{
		pair.second->SetTransform(Position(*pair.first), Angle(*pair.first));
		// pair.second->DestroyFixture(); //todo:
		// pair.second->CreateFixture()

		//todo set size
	}

	// Step the Box2D world simulation, only to handle the collisions
	_box2dWorldObject->Step(delta, 6, 2);

	// overwrite all positions, collisions are partly handled.
	int index = 0; //todo: for debug
	for (auto pair : _colliderToBodyMap)
	{
		//todo: does gameobject udate form this?
		pair.first->componentTransform->position = VecConvert(pair.second->GetPosition());

		BLOCKY_ENGINE_DEBUG_STREAM(index << ": " << tick <<
			"\tPosition: " << round(pair.second->GetPosition().x) << ", " << round(pair.second-> GetPosition().y) <<
			"\tVelocity: " << pair.second->GetLinearVelocity().Length() <<
			"\tGetMass: " << pair.second->GetMass());
		index++; //todo: for debug
	}

	tick++; //todo: for debug
}

b2Vec2 PhysicsModule::VecConvert(const glm::vec2& a)
{
	return {a.x, a.y};
}

glm::vec2 PhysicsModule::VecConvert(const b2Vec2& a)
{
	return {a.x, a.y};
}

b2Vec2 PhysicsModule::Position(const Collider& collider)
{
	return VecConvert(collider.componentTransform->position);
}

float PhysicsModule::Angle(const Collider& collider)
{
	//todo: add gameObject transforms
	return collider.componentTransform->rotation;
}

b2Body* PhysicsModule::createDynamicBody(b2World& world, const Collider& collider)
{
	float x = collider.componentTransform->position.x;
	float y = collider.componentTransform->position.y;
	float width = collider.componentTransform->scale.x;
	float height = collider.componentTransform->scale.y;
	float angle = collider.componentTransform->rotation;

	BLOCKY_ENGINE_DEBUG_STREAM("createDynamicBody: x: " << x << ", y: " << y << ", width: " << width << ", height: " <<
		height << ", angle: " << angle);

	// Define the first dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y); // Positioned left of center
	bodyDef.angle = angle;
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for the first dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(width, height);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	return body;
}

void PhysicsModule::AddCollider(Collider& collider)
{
	b2Body* body = createDynamicBody(*_box2dWorldObject, collider);

	_colliderToBodyMap[&collider] = body;
}

void PhysicsModule::RemoveCollider(Collider& collider)
{
	auto it = _colliderToBodyMap.find(&collider);
	if (it != _colliderToBodyMap.end())
	{
		_box2dWorldObject->DestroyBody(it->second);
		_colliderToBodyMap.erase(it);
	}
}
