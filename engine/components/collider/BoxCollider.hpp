//
// Created by hmkam on 19/11/2024.
//

#ifndef RECTANGLECOLLIDER_HPP
#define RECTANGLECOLLIDER_HPP
#include "Collider.hpp"

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height, float width);
	~BoxCollider() override = default;

	ColliderType GetType() override;

	[[nodiscard]] float GetWidth() const { return _width; }
	[[nodiscard]] float GetHeight() const { return _height; }

private:
	float _width, _height;
};

#endif //RECTANGLECOLLIDER_HPP
