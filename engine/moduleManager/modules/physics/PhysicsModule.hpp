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
	bool _gameObjectIsInitialized{};

	[[nodiscard]] b2Vec2 GetPosition() const {
		return b2body->GetPosition();
	}

	[[nodiscard]] float GetAngle() const {
		return b2body->GetAngle();
	}

	[[nodiscard]] b2Vec2 LastPosition() const {
		return _gameObjectLastPosition;
	}

	[[nodiscard]] float LastRotation() const {
		return _gameObjectLastRotation;
	}

	void LastPosition(b2Vec2 position) {
		_gameObjectLastPosition = position;
	}

	void LastRotation(float rotation) {
		_gameObjectLastRotation = rotation;
	}

	void SetTransform(const b2Vec2& position, float angle) {
		b2body->SetTransform(position, angle);
	}
};

class PhysicsModule : public ModuleWrapper {
public:
	PhysicsModule();
	~PhysicsModule() override = default;

	void Update(float delta) override;

	// when setting multiple different types of PhysicsBodies on the same gameObject will override partial properties
	void AddCollider(PhysicsBody& physicsBody);
	void RemoveCollider(const PhysicsBody& physicsBody);

private:
	void WritingExternalInputToBox2DWorld();
	void WritingBox2DWorldToOutside();

	b2Body* CreateBody(b2World& world, PhysicsBody& physicsBody);
	static void AddFixture(PhysicsBody& physicsBody, b2Body* body);

	static bool IsSame(const GameObject* gameObject, const Body* body);
	static b2Vec2 VecConvert(const glm::vec2& a);
	static glm::vec2 VecConvert(const b2Vec2& a);
	static b2Vec2 Position(const PhysicsBody& physicsBody);
	static b2Vec2 Position(const GameObject& gameObject);
	static float ToDegree(float radian);
	static float ToRadian(float degree);
	static float Angle(const PhysicsBody& physicsBody);
	static float Angle(const GameObject& gameObject);

	std::unique_ptr<b2World> _box2dWorldObject;
	std::unique_ptr<MyContactListener> _contactListener;
	std::unordered_map<GameObject*, Body*> _gameObjectToBodyMap;
	std::vector<std::unique_ptr<Body>> _bodies;
};

#endif //PHYSICSMODULE_HPP
