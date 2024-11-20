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
	// explicit Collider(GameObject& gameObject);
	Collider(GameObject& gameObject, const char* tag, ColliderType colliderType, bool isTrigger);
	~Collider() override;

	void Start() override;
	void Update(float delta) override;
	void End() override;

	void SetTriggerEnterCallback();
	void ClearTriggerEnterCallback();
	void SetTriggerExitCallback();
	void ClearTriggerExitCallback();

	bool isTrigger{false}; //todo: how should isTrigger be used?
	ColliderType _colliderType;
};

#endif //COLLIDER_HPP
