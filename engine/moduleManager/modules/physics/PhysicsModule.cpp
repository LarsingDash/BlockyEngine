#include "PhysicsModule.hpp"

#include <iostream>
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
}

PhysicsModule::~PhysicsModule()
{
	delete _world;
}

void PhysicsModule::Update(float delta)
{
	// 8 velocity iterations and 3 position iterations is a standard setting.
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	// Prepare for simulation. Typically we use a time step of 1/60 of a second.
	float timeStep = 1.0f / 60.0f;

	// Simulate the world for 60 steps.
	for (int32 i = 0; i < 430; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		_world->Step(timeStep, velocityIterations, positionIterations);

		// std::cout << i << "\t"
		// 	<< " body1: " << " Pos: (" << round(body1->GetPosition().x) << ", " << round(body1->GetPosition().y) <<
		// 		") Angle: " << round(body1->GetAngle())<<
		// 		", V: " << (round(body2->GetLinearVelocity().Length())) <<
		// 		", M: " << (round(body2->GetMass())) << "\t"
		// 	<< " body2: " << " Pos: (" << round(body2->GetPosition().x) << ", " << round(body2->GetPosition().y) <<
		// 		") Angle: " << round(body2->GetAngle()) <<
		// 		", V: " << (round(body2->GetLinearVelocity().Length())) <<
		// 		", M: " << (round(body2->GetMass())) << std::endl;
		for (auto pair : _colliderToBodyMap)
		{
			//todo: does gameobject udate form this?
			pair.first->componentTransform->position = VecConvert(pair.second->GetPosition());

			BLOCKY_ENGINE_DEBUG(std::to_string(i)+": " + std::to_string(tick) + ", " +
				std::to_string(pair.second->GetPosition().x) + ", " +std::to_string(pair.second->GetPosition().y) +
				", Velocity: " + std::to_string(round(pair.second->GetLinearVelocity().Length())) +
				", GetMass: " + std::to_string(round(pair.second->GetMass())));
		}
	}

	while (1)
	{
	}

	// //todo:
	// // delta = delta * 2000000;
	// // just overwrite all positions, this is done to separate the box2d lib form the rest of the project
	// // todo: write external input in box2d world
	// for (auto pair : _colliderToBodyMap)
	// {
	// 	// pair.second->
	// 	// pair.second->SetTransform(Position(*pair.first), Angle(*pair.first));
	// 	// BLOCKY_ENGINE_DEBUG("set: " +
	// 	// 	std::to_string(pair.second->GetPosition().x) + ", " +std::to_string(pair.second->GetPosition().x))
	// }
	//
	// // Step the Box2D world simulation, only to handle the collisions
	// _world->Step(delta, 6, 2);
	//
	// // just overwrite all positions, this is done to separate the box2d lib form the rest of the project
	// int index = 0;
	// for (auto pair : _colliderToBodyMap)
	// {
	// 	//todo: does gameobject udate form this?
	// 	pair.first->componentTransform->position = VecConvert(pair.second->GetPosition());
	//
	// 	BLOCKY_ENGINE_DEBUG(std::to_string(index)+": " + std::to_string(tick) + ", " +
	// 		std::to_string(pair.second->GetPosition().x) + ", " +std::to_string(pair.second->GetPosition().y) +
	// 		", Velocity: " + std::to_string(round(pair.second->GetLinearVelocity().Length())) +
	// 		", GetMass: " + std::to_string(round(pair.second->GetMass())));
	//
	// 	// std::cout << tick << "\t" << index
	// 	// 	<< "Pos: (" << round(pair.second->GetPosition().x) << ", " << round(pair.second->GetPosition().y)
	// 	// 	<< ") Angle: " << round(pair.second->GetAngle()) << std::endl;
	// 	index++;
	// }
	//
	// tick++;
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

b2Body* createDynamicBody(b2World& world, const Collider& collider)
{
	float x = collider.componentTransform->position.x;
	float y = collider.componentTransform->position.y;
	float width = collider.componentTransform->scale.x;
	float height = collider.componentTransform->scale.y;
	float angle = collider.componentTransform->rotation;

	std::cout << "createDynamicBody: x: " << x << ", y: " << y << ", width: " << width << ", height: " << height <<
		", angle: " << angle << std::endl;

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
	b2Body* body = createDynamicBody(*_world, collider);

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
