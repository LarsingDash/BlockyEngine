//
// Created by larsv on 27/12/2024.
//

#include "PathfindingGrid.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

PathfindingGrid::PathfindingGrid(
		GameObject* gameObject, const char* tag,
		int defaultWeight, glm::ivec2 dimensions) :
		Component(gameObject, tag, true),
		_renderingModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule()),
		_dimensions(dimensions), _grid() {
	_grid = std::vector<std::vector<Node>>(dimensions.y);

	for (int y = 0; y < dimensions.y; ++y) {
		auto& row = _grid[y] = std::vector<Node>(dimensions.x);

		for (int x = 0; x < row.size(); ++x) {
			row[x] = Node{
					.IsWalkable = true,
					.Weight = defaultWeight,
					.GridPos = {x, y}
			};
		}
	}
}

void PathfindingGrid::Start() {
	RefreshGridPositions();

	_visualize(_shouldVisualize);
}

void PathfindingGrid::Update(float delta) {}

void PathfindingGrid::End() {
	_visualize(false);
}

void PathfindingGrid::RefreshGridPositions() {
	auto& pos = componentTransform->GetWorldPosition();
	auto& scale = componentTransform->GetWorldScale();
	auto halfScale = scale / 2.f;

	float yStep = scale.y / static_cast<float>(_grid.size() - 1);

	for (int y = 0; y < _grid.size(); ++y) {
		auto& row = _grid[y];
		float xStep = scale.x / static_cast<float>(row.size() - 1);

		for (int x = 0; x < row.size(); ++x) {
			row[x].WorldPos = {
				xStep * static_cast<float>(x) - halfScale.x + pos.x,
				yStep * static_cast<float>(y) - halfScale.y + pos.y
			};
		}
	}
}

void PathfindingGrid::_visualize(bool show) {
	for (const auto& row : _grid) {
		for (const auto& node : row) {
			std::string name{tag + std::to_string(node.GridPos.x) + ',' + std::to_string(node.GridPos.y)};

			if (show)
				_renderingModule.AddDebugRectangle(
						name,
						[&node, &opacity = _opacity, &nodeSize = _nodeSize]
								(glm::vec2& position,
								 glm::vec2& size,
								 glm::ivec4& color) {
							position = node.WorldPos;
							size.x = size.y = nodeSize;

							if (!node.IsWalkable) color = {200, 0, 0, opacity};
							else color.a = opacity;
						});
			else _renderingModule.RemoveDebugRectangle(name);
		}
	}
}

Component* PathfindingGrid::_clone(const GameObject& parent) {
	auto clone = new PathfindingGrid(*this);
	return clone;
}
