//
// Created by hmkam on 25/11/2024.
//

#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP
#include <components/Component.hpp>
#include <components/collider/Collider.hpp>

//todo: add box and circle rigidBody

class RigidBody : public Component
{
public:
	RigidBody(GameObject& gameObject, const char* tag, bool effectedByGravity, bool friction);
	~RigidBody() override = default;

	void Start() override;

	void Update(float delta) override;

	void End() override;

	virtual PhysicsType GetType() = 0;

	bool effectedByGravity{false};
	float friction{0};
};

#endif //RIGIDBODY_HPP
