//
// Created by hmkam on 19/11/2024.
//

#include "PhysicsModule.hpp"

#include <algorithm>
#include <cmath>
#include <logging/BLogger.hpp>

#include "components/collider/CircleCollider.hpp"

PhysicsModule::PhysicsModule() = default;

PhysicsModule::~PhysicsModule() = default;

void PhysicsModule::Update(float delta)
{
	Collide();
	Resolve();
}

void PhysicsModule::Collide()
{
	std::vector<std::pair<Collider*, Collider*>> _toResolveList;
	// todo: quad tree

	for (Collider& collider1 : _collides)
	{
		for (Collider& collider2 : _collides)
		{
			if (&collider1 != &collider2 && DoOverlap(collider1, collider2))
			{
				// todo: don't check/add thestd::to_string( same pair twice
				_toResolveList.emplace_back(&collider1, &collider2);
			}
		}
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

// only use for axis-aligned rectangles.
bool PhysicsModule::DoOverlap(const Collider& collider1, const Collider& collider2)
{
	const CircleCollider* circleCollider1 = nullptr;
	const BoxCollider* boxCollider1 = nullptr;
	const CircleCollider* circleCollider2 = nullptr;
	const BoxCollider* boxCollider2 = nullptr;

	// Cast the first collider to the appropriate type
	switch (collider1._colliderType)
	{
	case ColliderType::CIRCLE:
		circleCollider1 = dynamic_cast<const CircleCollider*>(&collider1);
		break;
	case ColliderType::BOX:
		boxCollider1 = dynamic_cast<const BoxCollider*>(&collider1);
		break;
	}

	// Cast the second collider to the appropriate type
	switch (collider2._colliderType)
	{
	case ColliderType::CIRCLE:
		circleCollider2 = dynamic_cast<const CircleCollider*>(&collider2);
		break;
	case ColliderType::BOX:
		boxCollider2 = dynamic_cast<const BoxCollider*>(&collider2);
		break;
	}

	// Check for valid casts and call the appropriate overlap function
	if (circleCollider1 && circleCollider2)
	{
		return DoOverlap(*circleCollider1, *circleCollider2);
	}
	else if (boxCollider1 && boxCollider2)
	{
		return DoOverlap(*boxCollider1, *boxCollider2);
	}
	else if (circleCollider1 && boxCollider2)
	{
		return DoOverlap(*circleCollider1, *boxCollider2);
	}
	else if (boxCollider1 && circleCollider2)
	{
		return DoOverlap(*boxCollider1, *circleCollider2);
	}

	BLOCKY_ENGINE_ERROR("Collider cast error: " + collider1._colliderType + ' ' + collider2._colliderType);

	return false;
}

// only use for axis-aligned rectangles.
bool PhysicsModule::DoOverlap(const BoxCollider& box1, const BoxCollider& box2)
{
	return (
		box1.componentTransform->position.x <= box2.componentTransform->position.x + box2.componentTransform->scale.x &&
		box1.componentTransform->position.x + box1.componentTransform->scale.x >= box2.componentTransform->position.x &&
		box1.componentTransform->position.y <= box2.componentTransform->position.y + box2.componentTransform->scale.y &&
		box1.componentTransform->position.y + box1.componentTransform->scale.y >= box2.componentTransform->position.y
	);
}

// only use for axis-aligned rectangles.
bool PhysicsModule::DoOverlap(const BoxCollider& box, const CircleCollider& circle)
{
	return DoOverlap(circle, box);
}

// only use for axis-aligned rectangles. //todo: use standard @ etc.
bool PhysicsModule::DoOverlap(const CircleCollider& circle, const BoxCollider& box)
{
	struct dist
	{
		float x, y;
	};

	dist circleToBoxDistance{};
	circleToBoxDistance.x = std::abs(circle.componentTransform->position.x - box.componentTransform->position.x);
	circleToBoxDistance.y = std::abs(circle.componentTransform->position.y - box.componentTransform->position.y);

	if (circleToBoxDistance.x > (box.componentTransform->scale.x / 2 + circle.GetRadius())) { return false; }
	if (circleToBoxDistance.y > (box.componentTransform->scale.y / 2 + circle.GetRadius())) { return false; }

	if (circleToBoxDistance.x <= (box.componentTransform->scale.x / 2)) { return true; }
	if (circleToBoxDistance.y <= (box.componentTransform->scale.y / 2)) { return true; }

	const double cornerDistance_sq = std::pow(circleToBoxDistance.x - box.componentTransform->scale.x / 2, 2) +
		std::pow(circleToBoxDistance.y - box.componentTransform->scale.y / 2, 2);

	return cornerDistance_sq <= std::pow(circle.GetRadius(), 2);
}

// only use for axis-aligned rectangles.
bool PhysicsModule::DoOverlap(const CircleCollider& circle1, const CircleCollider& circle2)
{
	auto dx = circle1.componentTransform->position.x - circle2.componentTransform->position.x;
	auto dy = circle1.componentTransform->position.y - circle2.componentTransform->position.y;
	auto distance = std::sqrt(dx * dx + dy * dy);

	return distance < circle1.GetRadius() + circle2.GetRadius();
}
