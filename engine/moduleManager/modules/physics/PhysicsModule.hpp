//
// Created by hmkam on 19/11/2024.
//

#ifndef PHYSICSMODULE_HPP
#define PHYSICSMODULE_HPP
#include <memory>
#include <string>
#include <vector>
#include <moduleManager/ModuleWrapper.hpp>
#include "components/collider/BoxCollider.hpp"
#include "components/collider/CircleCollider.hpp"

//todo: PhysicsModule
class PhysicsModule : public ModuleWrapper
{
public:
	PhysicsModule();
	~PhysicsModule() override;

	void Update(float delta) override;
	void AddCollider(Collider& collider);
	void RemoveCollider(Collider& collider);

private:
	void Collide();
	void Resolve();

	[[nodiscard]] static bool DoOverlap(const Collider& collider1, const Collider& collider2);

	[[nodiscard]] static bool DoOverlap(const BoxCollider& box1, const BoxCollider& box2);
	[[nodiscard]] static bool DoOverlap(const BoxCollider& box, const CircleCollider& circle);
	[[nodiscard]] static bool DoOverlap(const CircleCollider& circle, const BoxCollider& box);
	[[nodiscard]] static bool DoOverlap(const CircleCollider& circle1, const CircleCollider& circle2);

	std::unique_ptr<PhysicsModule> _physicsModule;
	std::vector<std::reference_wrapper<Collider>> _collides;
	std::vector<std::pair<Collider*, Collider*>> _toResolveList;
};

#endif //PHYSICSMODULE_HPP
