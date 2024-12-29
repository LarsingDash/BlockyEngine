//
// Created by larsv on 28/12/2024.
//

#include "GridNavigator.hpp"

#include <gameObject/GameObject.hpp>

GridNavigator::GridNavigator(GameObject* gameObject, const char* tag, const char* gridTag,
							 glm::ivec2 startingGridPos, float movementSpeed) :
		Component(gameObject, tag, false), _gridTag(gridTag),
		_startingGridPos(startingGridPos), _movementSpeed(movementSpeed) {}

void GridNavigator::Start() {
	_grid = PathfindingGrid::GetGridByTag(_gridTag);

	auto& startingNode = (*_grid)(_startingGridPos.x, _startingGridPos.y);
	gameObject->transform->SetPosition(startingNode.WorldPos.x, startingNode.WorldPos.y);
	_currentNode = &startingNode;
}

void GridNavigator::Update(float delta) {
	if (!_path.empty()) {
		_elapsedTime += delta * _movementSpeed;

		if (_elapsedTime >= static_cast<float>(_currentNode->Weight)) {
			_currentNode = _path[_pathIndex];
			gameObject->transform->SetPosition(_currentNode->WorldPos.x, _currentNode->WorldPos.y);

			_elapsedTime = 0.f;
			++_pathIndex;

			if (_pathIndex == _path.size()) {
				_pathIndex = 1;
				_path.clear();

				_grid->ClearGridStatus();
				return;
			}
		}
	}
}

void GridNavigator::End() {}

void GridNavigator::SetTarget(const glm::vec2& worldPos) {
	_path = _grid->AStarPathfinding(
			*_currentNode,
			_grid->GetClosestNodeTo(worldPos)
	);

	//Cancel invalid paths
	if (_path.size() < 2) {
		_path.clear();
		_grid->ClearGridStatus();
	} else {
		_elapsedTime = 0.f;
		_pathIndex = 1;
	}
}

Component* GridNavigator::_clone(const GameObject& parent) {
	auto clone = new GridNavigator(*this);
	return clone;
}
