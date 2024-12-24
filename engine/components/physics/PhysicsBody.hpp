//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <functional>
#include <memory>

#include "components/Component.hpp"
#include "shape/Shape.hpp"

enum PhysicsType {
	COLLIDER,
	RIGIDBODY
};

struct TypeProperties {
	TypeProperties(PhysicsType physicsType, bool isStatic, glm::vec2 linearVelocity, float rotationVelocity,
	               float rotationResistance, float linearResistance, bool gravityEnabled):
		physicsType(physicsType),
		isStatic(isStatic),
		linearVelocity(linearVelocity),
		rotationVelocity(rotationVelocity),
		rotationResistance(rotationResistance),
		linearResistance(linearResistance),
		gravityEnabled(gravityEnabled) {}

	void SetLinearVelocity(const glm::vec2 newVelocity) {
		linearVelocity = newVelocity;
	}

	PhysicsType physicsType;
	bool isStatic;
	glm::vec2 linearVelocity;
	// in degree
	float rotationVelocity;
	float rotationResistance;
	float linearResistance;
	bool gravityEnabled;
};

class PhysicsBody : public Component {
public:
	PhysicsBody(GameObject* gameObject, const char* tag, PhysicsShape shape, const TypeProperties& typeProperties);
	~PhysicsBody() override = default;

	PhysicsBody(const PhysicsBody& other) = default;

	void Start() override;
	void Update(float delta) override;
	void End() override;

	void SetOnEnter(const std::function<void(GameObject& other)>& callback);
	void SetOnExit(const std::function<void(GameObject& other)>& callback);

	[[nodiscard]] virtual PhysicsShape GetShape();
	[[nodiscard]] virtual std::shared_ptr<TypeProperties> GetTypeProperties();
	[[nodiscard]] const TypeProperties& ReadTypeProperties() const;

private:
	Component* _clone(const GameObject& parent) override;
	//Private
	std::function<void(GameObject& other)> enter{nullptr};
	std::function<void(GameObject& other)> exit{nullptr};

	PhysicsShape _shape;
	std::shared_ptr<TypeProperties> _typeProperties;
};
#endif //PHYSICSBODY_HPP
