//
// Created by hmkam on 19/11/2024.
//
#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/vec2.hpp>

enum PhysicsShape {
	BOX,
	CIRCLE
};

class Shape //todo:
{
public:
	Shape(bool isTrigger, bool isStatic);
	virtual ~Shape();

	void CollisionCallback(Shape& other); //todo: check
	//todo: add subscribe to callback function

	virtual PhysicsShape GetType() = 0;

	bool isTrigger{false};
	bool isStatic{false};
};
#endif //COLLIDER_HPP
