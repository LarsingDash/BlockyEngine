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
	float mutable _width, _height;

	// void SetWidth(float width) { _width = width; }
	// void SetHeight(const float height) { _height = height; }

	friend class PhysicsBody;
};

#endif //BOX_HPP