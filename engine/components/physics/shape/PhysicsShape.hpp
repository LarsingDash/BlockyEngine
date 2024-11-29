//
// Created by hmkam on 19/11/2024.
//
#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/vec2.hpp>

enum PhysicsType {
	BOX,
	CIRCLE
};

class PhysicsShape //todo:
{
public:
	PhysicsShape(bool isTrigger, bool isStatic);
	virtual ~PhysicsShape();

	void CollisionCallback(PhysicsShape& other); //todo: check
	//todo: add subscribe to callback function

	virtual PhysicsType GetType() = 0;

	bool isTrigger{false};
	bool isStatic{false};
};
#endif //COLLIDER_HPP
