//
// Created by hmkam on 19/11/2024.
//

#ifndef PHYSICSMODULE_HPP
#define PHYSICSMODULE_HPP
#include <memory>
#include <unordered_map>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <Box2D/b2_world.h>
#include <moduleManager/ModuleWrapper.hpp>
#include "components/physics/physicsBody/PhysicsBody.hpp"
#include "MyContactListener.hpp"

struct b2BodyDef;
class b2Body;
class b2World;

class PhysicsModule : public ModuleWrapper {
public:
	PhysicsModule();
	~PhysicsModule() override = default;

	void Update(float delta) override;
	static bool IsSame(const PhysicsBody* collider, const b2Body* body);
	void AddCollider(PhysicsBody& collider);
	void RemoveCollider(PhysicsBody& collider);

private:
	void WritingExternalInputToBox2DWorld();
	void WritingBox2DWorldToOutside();

	static b2Body* CreateBody(b2World& world, PhysicsBody& collider);
	// void AddFixture(RigidBody& rigidBody, b2Body* body);
	static void AddFixture(PhysicsBody& collider, b2Body* body);
	// b2Body* CreateBody(b2World& world, RigidBody& rigidBody);

	static b2Vec2 VecConvert(const glm::vec2& a);
	static glm::vec2 VecConvert(const b2Vec2& a);
	static b2Vec2 Position(const PhysicsBody& collider);
	static float Angle(const PhysicsBody& collider);

	std::unique_ptr<b2World> _box2dWorldObject;
	std::unique_ptr<MyContactListener> _contactListener;
	std::unordered_map<PhysicsBody*, b2Body*> _colliderToBodyMap;
};

#endif //PHYSICSMODULE_HPP
