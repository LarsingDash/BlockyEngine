//
// Created by hmkam on 19/11/2024.
//

#ifndef RECTANGLECOLLIDER_HPP
#define RECTANGLECOLLIDER_HPP
#include "Collider.hpp"

class RectangleCollider : public Collider
{
public:
	// explicit RectangleCollider(GameObject& gameObject);
	RectangleCollider(GameObject& gameObject, const char* tag, bool isTrigger);
	~RectangleCollider() override = default;

private:
	float _width, _height;
};

#endif //RECTANGLECOLLIDER_HPP
