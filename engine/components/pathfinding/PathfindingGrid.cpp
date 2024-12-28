//
// Created by larsv on 27/12/2024.
//

#include "PathfindingGrid.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

PathfindingGrid::PathfindingGrid(
		GameObject* gameObject, const char* tag,
		int defaultWeight, glm::ivec2 dimensions,
		bool shouldVisualize) :
		Component(gameObject, tag),
		_renderingModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule()),
		_shouldVisualize(shouldVisualize), _dimensions(dimensions), _grid() {
	_grid = std::vector<std::vector<GridNode>>(dimensions.y);

	for (int y = 0; y < dimensions.y; ++y) {
		auto& row = _grid[y] = std::vector<GridNode>(dimensions.x);

		for (int x = 0; x < row.size(); ++x) {
			row[x] = GridNode(defaultWeight, {x, y});
		}
	}
}

void PathfindingGrid::Start() {
	Visualize(_shouldVisualize);
}

void PathfindingGrid::Update(float delta) {}

void PathfindingGrid::End() {
	Visualize(false);
}

void PathfindingGrid::Visualize(bool show) {
	for (const auto& row : _grid) {
		for (const auto& node : row) {
			std::string name{tag + std::to_string(node._gridPos.x) + ',' + std::to_string(node._gridPos.y)};

			if (show)
				_renderingModule.AddDebugRectangle(
						name,
						[&node, &opacity = _opacity]
								(glm::vec2& position,
								 glm::vec2& size,
								 glm::ivec4& color) {
							position = node._gridPos * 75;
							size.x = size.y = 50.f;

							if (!node._isWalkable) color = {200, 0, 0, opacity};
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
