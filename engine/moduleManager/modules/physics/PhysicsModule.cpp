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
	_world = new b2World(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 50.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
}

PhysicsModule::~PhysicsModule()
{
	delete _world;
}

void PhysicsModule::Update(float delta)
{
	//todo:
	// delta = delta * 2000000;
	// just overwrite all positions, this is done to separate the box2d lib form the rest of the project
	// todo: write external input in box2d world
	for (auto pair : _colliderToBodyMap)
	{
		// pair.second->
		pair.second->SetTransform(Position(*pair.first), Angle(*pair.first));
		BLOCKY_ENGINE_DEBUG("set: " +
			std::to_string(pair.second->GetPosition().x) + ", " +std::to_string(pair.second->GetPosition().x))
	}

	// Step the Box2D world simulation, only to handle the collisions
	_world->Step(delta, 6, 2);

	// just overwrite all positions, this is done to separate the box2d lib form the rest of the project
	for (auto pair : _colliderToBodyMap)
	{
		BLOCKY_ENGINE_DEBUG(std::to_string(delta) + ": " +
			std::to_string(pair.second->GetPosition().x) + ", " +std::to_string(pair.second->GetPosition().x))
		//todo: does gameobject udate form this?
		pair.first->componentTransform->position = VecConvert(pair.second->GetPosition());

		BLOCKY_ENGINE_DEBUG("Velocity: " + std::to_string(pair.second->GetLinearVelocity().Length()) +
			", GetMass: " + std::to_string(pair.second->GetMass()));
	}
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

b2BodyDef PhysicsModule::SetBodyDef(Collider& collider)
{
	b2BodyDef bodyDef;

	//todo: add gameObject transforms
	b2Vec2 position = Position(collider);
	float rotation = Angle(collider);

	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.0f;

	// Scale (if applicable) todo:
	// Box2D doesn't directly use scale, so you might need to adjust shape sizes accordingly
	//glm::vec2 scale = Add (collider.componentTransform->scale,collider.gameObject.transform->scale);
	// glm::vec2 scale = collider.componentTransform->scale;

	//todo: if box if circle

	// Position
	bodyDef.position.Set(position.x, position.y);

	// Rotation (assuming Box2D uses radians)
	bodyDef.angle = rotation;

	// ... other bodyDef properties (e.g., type, mass, etc.)todo:
	return bodyDef;
}

// b2FixtureDef* PhysicsModule::SetFixtureDef()
// {
//
//
// 	return &fixtureDef;
// }

void PhysicsModule::AddCollider(Collider& collider)
{
	b2BodyDef bodyDef = SetBodyDef(collider);

	b2Body* body = _world->CreateBody(&bodyDef);

	//todo: func
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(100.0f, 100.0f); //todo: box circle collider attirbutes

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 0.01f;

	// Override the default friction.
	fixtureDef.friction = 0.0f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	_colliderToBodyMap[&collider] = body;
}

void PhysicsModule::RemoveCollider(Collider& collider)
{
	auto it = _colliderToBodyMap.find(&collider);
	if (it != _colliderToBodyMap.end())
	{
		_world->DestroyBody(it->second);
		_colliderToBodyMap.erase(it);
	}
}
