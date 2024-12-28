//
// Created by larsv on 27/12/2024.
//

#include "PathfindingGrid.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

PathfindingGrid::PathfindingGrid(const char* tag, int defaultWeight, glm::ivec2 dimensions) :
		_renderingModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule()),
		_tag(tag), _dimensions(dimensions), _grid() {
	_grid = std::vector<std::vector<GridNode>>(dimensions.y);

	for (int y = 0; y < dimensions.y; ++y) {
		auto& row = _grid[y] = std::vector<GridNode>(dimensions.x);

		for (int x = 0; x < row.size(); ++x) {
			row[x] = GridNode(defaultWeight, {x, y});
		}
	}
}

void PathfindingGrid::Visualize(bool show) {
	for (const auto& row : _grid) {
		for (const auto& node : row) {
			std::string name{_tag + std::to_string(node._gridPos.x) + ',' + std::to_string(node._gridPos.y)};

			if (show)
				_renderingModule.AddDebugRectangle(
						name,
						[&node]
								(glm::vec2& position,
								 glm::vec2& size,
								 glm::ivec3& color) {
							position = node._gridPos * 75;
							size.x = size.y = 50.f;
						});
			else _renderingModule.RemoveDebugRectangle(name);
		}
	}
}
