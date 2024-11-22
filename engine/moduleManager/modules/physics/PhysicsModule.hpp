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
#include "components/collider/Collider.hpp"

struct b2BodyDef;
class b2Body;
class b2World;

//todo: PhysicsModule
class PhysicsModule : public ModuleWrapper
{
public:
	PhysicsModule();
	~PhysicsModule() override = default;

	void Update(float delta) override;
	void AddCollider(Collider& collider);
	void RemoveCollider(Collider& collider);

private:
	void WritingExternalInputToBox2DWorld();
	void WritingBox2DWorldToOutside();

	static b2Body* CreateBody(b2World& world, Collider& collider);
	static void AddFixture(Collider& collider, b2Body* body);

	static b2Vec2 VecConvert(const glm::vec2& a);
	static glm::vec2 VecConvert(const b2Vec2& a);
	static b2Vec2 Position(const Collider& collider);
	static float Angle(const Collider& collider);
	static b2Vec2 Dimensions(const Collider& collider);

	std::unique_ptr<b2World> _box2dWorldObject;
	// std::unique_ptr<MyContactListener> _contactListener;
	std::unordered_map<Collider*, b2Body*> _colliderToBodyMap;

	int tick = 0; //todo: for debug
};

#endif //PHYSICSMODULE_HPP
