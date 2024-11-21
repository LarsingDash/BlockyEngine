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
	static b2BodyDef SetBodyDef(const Collider& collider);
	b2FixtureDef* SetFixtureDef();

	void AddCollider(b2Body* body);
	void RemoveCollider(b2Body* body);
	void Collide();
	void Resolve();

	[[nodiscard]] static bool DoOverlap(const Collider& collider1, const Collider& collider2);

	[[nodiscard]] static bool DoOverlap(const BoxCollider& box1, const BoxCollider& box2);
	[[nodiscard]] static bool DoOverlap(const BoxCollider& box, const CircleCollider& circle);
	[[nodiscard]] static bool DoOverlap(const CircleCollider& circle, const BoxCollider& box);
	[[nodiscard]] static bool DoOverlap(const CircleCollider& circle1, const CircleCollider& circle2);

	std::unique_ptr<PhysicsModule> _physicsModule;
	std::vector<std::reference_wrapper<Collider>> _collides;
	std::vector<std::pair<std::reference_wrapper<Collider>*, std::reference_wrapper<Collider>*>> _toResolveList;
	//todo: reference_wrapper

	b2World* _world; // Box2D world object
	std::vector<b2BodyDef*> _colliders; // Keep track of bodies

	// Map to store a reference to the Collider object and its corresponding b2Body
	std::unordered_map<Collider*, b2Body*> _colliderToBodyMap;

	int tick = 0;
};

#endif //PHYSICSMODULE_HPP
