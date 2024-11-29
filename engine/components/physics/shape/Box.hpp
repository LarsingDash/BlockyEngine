//
// Created by hmkam on 19/11/2024.
//

#ifndef BOX_HPP
#define BOX_HPP
#include "PhysicsShape.hpp"

class Box : public PhysicsShape {
public:
	Box(bool isTrigger, bool isStatic, float height, float width);
	~Box() override = default;

	PhysicsType GetType() override;

	[[nodiscard]] float GetWidth() const { return _width; }
	[[nodiscard]] float GetHeight() const { return _height; }

private:
	float _width, _height;
};

#endif //BOX_HPP