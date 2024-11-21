#include "PhysicsModule.hpp"

#include <Box2D/Box2D.h>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

//todo:for box and circle
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
		// todo: only update if needed
		pair.second->SetTransform(Position(*pair.first), Angle(*pair.first));

		// todo: only update if needed
		// Destroy all existing fixtures so if there is a resize the resize can be applied
		for (b2Fixture* fixture = pair.second->GetFixtureList(); fixture;)
		{
			b2Fixture* next = fixture->GetNext();
			pair.second->DestroyFixture(fixture);
			fixture = next;
		}

		AddFixture(pair.second, Dimensions(*pair.first));
	}

	// Step the Box2D world simulation, only to handle the collisions
	_box2dWorldObject->Step(delta, 6, 2);

	// overwrite all positions, collisions are partly handled.
	for (auto pair : _colliderToBodyMap)
	{
		//todo: does gameobject udate form this?
		pair.first->componentTransform->position = VecConvert(pair.second->GetPosition());

		BLOCKY_ENGINE_DEBUG_STREAM(tick <<
			"\tPosition: " << round(pair.second->GetPosition().x) << ", " << round(pair.second-> GetPosition().y) <<
			"\tVelocity: " << pair.second->GetLinearVelocity().Length() <<
			"\tGetMass: " << pair.second->GetMass());
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

b2Vec2 PhysicsModule::Dimensions(const Collider& collider)
{
	//todo: add gameObject transforms
	return VecConvert(collider.componentTransform->scale);
}

void PhysicsModule::AddFixture(b2Body* body, b2Vec2 dimensions)
{
	// Define another box shape for the first dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(dimensions.x, dimensions.y);
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
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

	AddFixture(body, {width, height});

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
