//
// Created by larsv on 28/12/2024.
//

#include "GridNavigator.hpp"

#include <gameObject/GameObject.hpp>

GridNavigator::GridNavigator(GameObject* gameObject, const char* tag, const char* gridTag) :
		Component(gameObject, tag, false), _gridTag(gridTag) {}

#include <iostream>
void GridNavigator::Start() {
	_grid = PathfindingGrid::GetGridByTag(_gridTag);
}

void GridNavigator::Update(float delta) {}

void GridNavigator::End() {}

void GridNavigator::SetTarget(const glm::vec2& worldPos) {
	_grid->GetClosestNodeTo(worldPos).IsWalkable = false;
}

Component* GridNavigator::_clone(const GameObject& parent) {
	auto clone = new GridNavigator(*this);
	return clone;
}
