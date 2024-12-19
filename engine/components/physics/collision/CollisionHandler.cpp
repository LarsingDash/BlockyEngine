//
// Created by hmkam on 03/12/2024.
//

#include "CollisionHandler.hpp"

#include <utility>
#include <components/physics/PhysicsBody.hpp>
#include <gameObject/GameObject.hpp>

CollisionHandler::CollisionHandler(GameObject* gameObject, const char* tag, const PhysicsBody& body,
                                   std::function<void(GameObject&)> onEntryCallback,std::function<void(GameObject&)> onExitCallback) :
	Component(gameObject, tag, false), _onEntryHandler(std::move(onEntryCallback)), _onExitHandler(std::move(onExitCallback)), _body(body) {}

void CollisionHandler::Start() {
	_body.SetOnEnter(_onEntryHandler);
	_body.SetOnExit(_onExitHandler);
}

void CollisionHandler::End() {
	_body.SetOnEnter(nullptr);
	_body.SetOnEnter(nullptr);
}


Component * CollisionHandler::_clone(const GameObject &parent) {
	return new CollisionHandler(*this);
}