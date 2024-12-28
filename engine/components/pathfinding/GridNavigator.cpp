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
	std::cout << (*_grid)(4, 8).Weight << std::endl;
}

void GridNavigator::Update(float delta) {}

void GridNavigator::End() {}

Component* GridNavigator::_clone(const GameObject& parent) {
	auto clone = new GridNavigator(*this);
	return clone;
}