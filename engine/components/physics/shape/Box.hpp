//
// Created by hmkam on 19/11/2024.
//

#ifndef BOX_HPP
#define BOX_HPP
#include "Shape.hpp"

class Box : public Shape {
public:
	Box(float height, float width);
	~Box() override = default;

	PhysicsShape GetShape() override;

	[[nodiscard]] float GetWidth() const { return _width; }
	[[nodiscard]] float GetHeight() const { return _height; }

private:
	mutable float _width, _height;

	friend class PhysicsBody;
};

#endif //BOX_HPP
