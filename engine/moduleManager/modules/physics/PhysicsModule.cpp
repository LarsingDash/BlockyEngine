// //
// // Created by hmkam on 19/11/2024.
// //
//
// #include "PhysicsModule.hpp"
//
// #include <algorithm>
//
// PhysicsModule::PhysicsModule() = default;
//
// PhysicsModule::~PhysicsModule() = default;
//
// void PhysicsModule::Update(float delta)
// {
// 	Collide();
// 	Resolve();
// }
//
// void PhysicsModule::Collide()
// {
// 	for (Collider& collider : _collides)
// 	{
// 		switch (collider.GetColliderType())
// 		{
// 		case RECTANGLE:
// 			collider.Update();
// 			RectangleCollider(reinterpret_cast<RectangleCollider&>(collider));
// 			break;
// 		}
// 	}
// }
//
// void PhysicsModule::Resolve()
// {
// 	//todo: resolve physics
// 	// for (Collider& collider : _collides)
// 	// {
// 	// 	switch (collider.GetColliderType())
// 	// 	{
// 	// 	case RECTANGLE:
// 	// 		RectangleCollider(reinterpret_cast<RectangleCollider&>(collider));
// 	// 		break;
// 	// 	}
// 	// }
// }
//
// void PhysicsModule::AddCollide(Collider& collider)
// {
// 	_collides.emplace_back(collider);
// }
//
// void PhysicsModule::RemoveCollide(Collider& collider)
// {
// 	auto it = std::find_if(_collides.begin(), _collides.end(),
// 	                       [&collider](const std::reference_wrapper<Collider>& other)
// 	                       {
// 		                       return &collider == &other.get();
// 	                       });
//
// 	if (it != _collides.end())
// 	{
// 		_collides.erase(it);
// 	}
// }
//
