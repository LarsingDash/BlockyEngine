//
// Created by hmkam on 03/12/2024.
//

#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include <functional>
#include <components/Component.hpp>

class CollisionHandler : public Component {
public:
	CollisionHandler(GameObject* gameObject, const char* tag,
	                 std::function<void(GameObject*, GameObject*)> customCollisionHandler);
	~CollisionHandler() override = default;

	virtual void HandleCollision(GameObject* obj1, GameObject* obj2);

	void Start() override {};
	void Update(float delta) override {};
	void End() override {};

private:
	std::function<void(GameObject*, GameObject*)> _customCollisionHandler;
};

#endif //COLLISIONHANDLER_HPP
