//
// Created by hmkam on 19/11/2024.
//

#include "PhysicsModule.hpp"

#include <algorithm>
#include <logging/BLogger.hpp>

PhysicsModule::PhysicsModule() = default;

PhysicsModule::~PhysicsModule() = default;

void PhysicsModule::Update(float delta)
{
	Collide();
	Resolve();
}

void PhysicsModule::Collide()
{
	for (Collider& collider : _collides)
	{
		// BLOCKY_ENGINE_DEBUG("coliders: " + collider.tag);
		// switch (collider._colliderType)
		// {
		// case RECTANGLE:
		// 	RectangleCollider(reinterpret_cast<RectangleCollider&>(collider));
		// 	break;
		//   default: ;
		//   }
	}
}

void PhysicsModule::Resolve()
{
	// BLOCKY_ENGINE_DEBUG("Resolve");

	//todo: resolve physics
	// for (Collider& collider : _collides)
	// {
	// 	switch (collider.GetColliderType())
	// 	{
	// 	case RECTANGLE:
	// 		RectangleCollider(reinterpret_cast<RectangleCollider&>(collider));
	// 		break;
	// 	}
	// }
}

void PhysicsModule::AddCollider(Collider& collider)
{
	_collides.emplace_back(collider);
}

void PhysicsModule::RemoveCollider(Collider& collider)
{
	auto it = std::find_if(_collides.begin(), _collides.end(),
	                       [&collider](const std::reference_wrapper<Collider>& other)
	                       {
		                       return &collider == &other.get();
	                       });

	if (it != _collides.end())
	{
		_collides.erase(it);
	}
}

