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
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>
#include <moduleManager/ModuleWrapper.hpp>
#include "components/physics/PhysicsBody.hpp"
#include "MyContactListener.hpp"

struct b2BodyDef;
class b2Body;
class b2World;

struct Body {
	b2Body* b2body{};
	b2Vec2 _gameObjectLastPosition{};
	float _gameObjectLastRotation{};

	b2Vec2 _physicsBodyLastLinearVelocity{};
	float _physicsBodyLastLinearResistance{};
	float _physicsBodyLastRotationVelocity{};
	float _physicsBodyLastRotationResistance{};

	bool _gameObjectIsInitialized{};

	[[nodiscard]] b2Vec2 GetPosition() const { return b2body->GetPosition(); }
	// Return rotation in radian
	[[nodiscard]] float GetAngle() const { return b2body->GetAngle(); }
	[[nodiscard]] b2Vec2 GetLinearVelocity() const { return b2body->GetPosition(); }
	// Return rotation in radian
	[[nodiscard]] float GetRotationVelocity() const { return b2body->GetAngle(); }
	// Return rotation in radian
	[[nodiscard]] float GetRotationResistance() const { return b2body->GetAngularDamping(); }
	[[nodiscard]] float GetLinearResistance() const { return b2body->GetLinearDamping(); }

	[[nodiscard]] b2Vec2 LastPosition() const { return _gameObjectLastPosition; }
	// Return rotation in radian
	[[nodiscard]] float LastRotation() const { return _gameObjectLastRotation; }
	[[nodiscard]] b2Vec2 PhysicsBodyLastLinearVelocity() const { return _physicsBodyLastLinearVelocity; }
	[[nodiscard]] float PhysicsBodyLastLinearResistance() const { return _physicsBodyLastLinearResistance; }
	// Return rotation in radian
	[[nodiscard]] float PhysicsBodyLastRotationVelocity() const { return _physicsBodyLastRotationVelocity; }
	// Return rotation in radian
	[[nodiscard]] float PhysicsBodyLastRotationResistance() const { return _physicsBodyLastRotationResistance; }

	void LastPosition(const b2Vec2 position) { _gameObjectLastPosition = position; }
	// Rotation in radian
	void LastRotation(const float rotation) { _gameObjectLastRotation = rotation; }
	void PhysicsBodyLastLinearVelocity(b2Vec2 velocity) { _physicsBodyLastLinearVelocity = velocity; }
	void PhysicsBodyLastLinearResistance(float resistance) { _physicsBodyLastLinearResistance = resistance; }
	// Rotation in radian
	void PhysicsBodyLastRotationVelocity(float velocity) { _physicsBodyLastRotationVelocity = velocity; }
	// Rotation in radian
	void PhysicsBodyLastRotationResistance(float resistance) { _physicsBodyLastRotationResistance = resistance; }

	// Rotation in radian
	void SetTransform(const b2Vec2& position,
	                  const float angle,
	                  const b2Vec2& linearVelocity,
	                  const float rotationVelocity,
	                  const float linearResistance,
	                  const float rotationResistance) const {
		b2body->SetTransform(position, angle);
		b2body->SetLinearVelocity(linearVelocity);
		b2body->SetAngularVelocity(rotationVelocity);
		b2body->SetLinearDamping(linearResistance);
		b2body->SetAngularDamping(rotationResistance);
	}
};

class PhysicsModule : public ModuleWrapper {
public:
	PhysicsModule();
	~PhysicsModule() override = default;

	void Update(float delta) override;
	void FixedUpdate(float delta);

	// when setting multiple different types of PhysicsBodies on the same gameObject will override partial properties
	void AddPhysicsBody(PhysicsBody& physicsBody);
	void RemovePhysicsBody(PhysicsBody& physicsBody);

private:
	void _writingExternalInputToBox2DWorld();
	void _writingBox2DWorldToOutside();

	void _createPhysicsBody(PhysicsBody& physicsBody);
	b2Body* _createBody(b2World& world, PhysicsBody& physicsBody);
	static void _addFixture(PhysicsBody& physicsBody, b2Body* body);

	static void _updateBox2DIfChanges(const PhysicsBody* physicsBody, Body* body);
	static b2Vec2 _vecConvert(const glm::vec2& a);
	static glm::vec2 _vecConvert(const b2Vec2& a);
	static b2Vec2 _position(const PhysicsBody& physicsBody);
	static b2Vec2 _linearVelocity(const PhysicsBody& physicsBody);
	static float _rotationVelocity(const PhysicsBody& physicsBody);
	static float _rotationResistance(const PhysicsBody& physicsBody);
	static float _linearResistance(const PhysicsBody& physicsBody);
	static float _toDegree(float radian);
	static float _toRadian(float degree);
	static float _angle(const PhysicsBody& physicsBody);

	std::unique_ptr<b2World> _box2dWorldObject;
	std::unique_ptr<MyContactListener> _contactListener;
	std::unordered_map<PhysicsBody*, Body*> _gameObjectToBodyMap;
	std::vector<std::unique_ptr<Body>> _bodies;
};

#endif //PHYSICSMODULE_HPP
