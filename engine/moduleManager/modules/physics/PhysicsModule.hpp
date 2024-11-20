// //
// // Created by hmkam on 19/11/2024.
// //
//
// #ifndef PHYSICSMODULE_HPP
// #define PHYSICSMODULE_HPP
// #include <memory>
// #include <string>
// #include <vector>
// #include <moduleManager/ModuleWrapper.hpp>
// #include "components/collider/RectangleCollider.hpp"
//
// //todo: PhysicsModule
// class PhysicsModule : public ModuleWrapper
// {
// public:
// 	PhysicsModule();
// 	~PhysicsModule() override;
//
// 	void Update(float delta) override;
// 	void AddCollide(Collider& collider);
// 	void RemoveCollide(Collider& collider);
//
// private:
// 	void Collide();
// 	void Resolve();
//
// 	std::unique_ptr<PhysicsModule> _physicsModule;
// 	std::vector<std::reference_wrapper<Collider>> _collides;
// };
//
// #endif //PHYSICSMODULE_HPP
