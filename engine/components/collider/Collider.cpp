//
// Created by hmkam on 19/11/2024.
//

#include "Collider.hpp"

Collider::Collider(GameObject& gameObject, const char* tag, ColliderType colliderType, bool isTrigger) :
	Component(gameObject, tag), isTrigger(isTrigger), _colliderType(colliderType)
{
}

Collider::~Collider() = default;

void Collider::Start()
{
	//	ModuleManager::getInstance().getModule<WindowModule>().AddCollider(*this);
}

void Collider::Update(float delta)
{
	//todo: Collider::Update
}

void Collider::End()
{
	//	ModuleManager::getInstance().getModule<WindowModule>().RemoveCollider(*this);
}

// ColliderType Collider::GetColliderType()
// {
// 	return _colliderType;
// }
