//
// Created by hmkam on 19/11/2024.
//

#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <components/Component.hpp>

enum ColliderType
{
	BOX,
	CIRCLE
};

class Collider : public Component
{
public:
	Collider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic);
	~Collider() override;

	void Start() override;

	void Update(float delta) override;

	void End() override;

	void CollisionCallback(Collider& other);
	virtual ColliderType GetColliderType() = 0;

	bool isTrigger{false};
	bool isStatic{false};
};

#endif //COLLIDER_HPP
