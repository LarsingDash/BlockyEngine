//
// Created by hmkam on 19/11/2024.
//
#ifndef SHAPE_HPP
#define SHAPE_HPP

//todo: delete?
enum PhysicsShape {
	BOX,
	CIRCLE
};

class Shape {
public:
	Shape() = default;
	virtual ~Shape() = default;

	virtual PhysicsShape GetShape() = 0;
};
#endif //SHAPE_HPP
