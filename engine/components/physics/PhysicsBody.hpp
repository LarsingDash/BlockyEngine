//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <functional>
#include <memory>

#include "components/Component.hpp"
#include "components/physics/shape/Shape.hpp"

enum PhysicsType {
	COLLIDER,
	RIGIDBODY
};

struct TypeProperties {
	TypeProperties(PhysicsType physicsType, bool isStatic, glm::vec2 velocity, float rotationVelocity,
	               float angularResistance, float linearResistance, bool gravityEnabled): physicsType(physicsType),
		isStatic(isStatic), velocity(velocity),
		rotationVelocity(rotationVelocity),
		angularResistance(angularResistance),
		linearResistance(linearResistance),
		gravityEnabled(gravityEnabled) {}

	void SetVelocity(const glm::vec2 newVelocity)
	{
		velocity = newVelocity;
	}

	PhysicsType physicsType;
	bool isStatic;
	glm::vec2 velocity;
	float rotationVelocity;
	float angularResistance;
	float linearResistance;
	bool gravityEnabled;
};

class PhysicsBody : public Component {
public:
	PhysicsBody(GameObject* gameObject, const char* tag, std::shared_ptr<Shape> physicsBody,
	            const TypeProperties& typeProperties);
	~PhysicsBody() override = default;

	PhysicsBody(const PhysicsBody& other) = default;

	void Start() override;
	void Update(float delta) override;
	void End() override;


	void SetOnEnter(const std::function<void(GameObject& other)> &callback);
	void SetOnExit(const std::function<void(GameObject& other)> &callback);


	[[nodiscard]] virtual std::shared_ptr<Shape>& GetShapeReference();
	[[nodiscard]] virtual PhysicsShape GetShape();
	[[nodiscard]] virtual TypeProperties GetTypeProperties() const;

private:
	Component* _clone(const GameObject& parent) override;
	//Private
	std::function<void(GameObject& other)> enter {nullptr};
	std::function<void(GameObject& other)> exit {nullptr};

	std::shared_ptr<Shape> _physicsShape;
	TypeProperties _typeProperties;
};
#endif //PHYSICSBODY_HPP