//
// Created by hmkam on 19/11/2024.
//

#ifndef PHYSICSMODULE_HPP
#define PHYSICSMODULE_HPP
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <moduleManager/ModuleWrapper.hpp>
#include "components/collider/BoxCollider.hpp"
#include "components/collider/CircleCollider.hpp"

struct b2BodyDef;
class b2Body;
class b2World;

//todo: PhysicsModule
class PhysicsModule : public ModuleWrapper
{
public:
	PhysicsModule();
	~PhysicsModule() override;

	void Update(float delta) override;
	void AddCollider(Collider& collider);
	void RemoveCollider(Collider& collider);

private:
	static b2Vec2 VecConvert(const glm::vec2& a);
	static glm::vec2 VecConvert(const b2Vec2& a);
	static b2Vec2 Position(const Collider& collider);
	static float Angle(const Collider& collider);
	static b2Body* createDynamicBody(b2World& world, const Collider& collider);

	b2World* _box2dWorldObject;
	std::unordered_map<Collider*, b2Body*> _colliderToBodyMap;

	int tick = 0; //todo: for debug
};

#endif //PHYSICSMODULE_HPP
