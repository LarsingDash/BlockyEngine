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
	auto& target = _grid->GetClosestNodeTo(worldPos);
	auto path = _grid->AStarPathfinding((*_grid)(0,0), target);
//	std::cout << "---------------" << std::endl;
//	for (const auto& node : path) std::cout << node->GridPos.x << ' ' << node->GridPos.y << std::endl;
}

Component* GridNavigator::_clone(const GameObject& parent) {
	auto clone = new GridNavigator(*this);
	return clone;
}
