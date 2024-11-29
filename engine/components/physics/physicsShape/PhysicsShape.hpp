//
// Created by hmkam on 19/11/2024.
//
#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <components/Component.hpp>

enum PhysicsType {
	BOX,
	CIRCLE
};

class PhysicsShape //todo:
{
public:
	PhysicsShape(bool isTrigger, bool isStatic);
	virtual ~PhysicsShape();

	void CollisionCallback(PhysicsShape& other); //todo:
	virtual PhysicsType GetType() = 0;

	bool isTrigger{false};
	bool isStatic{false};
};
#endif //COLLIDER_HPP
