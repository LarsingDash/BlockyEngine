//
// Created by larsv on 27/12/2024.
//

#include "GridGraph.hpp"

GridGraph::GridGraph(int defaultWeight, glm::ivec2 dimensions) :
		_dimensions(dimensions), _grid() {
	_grid = std::vector<std::vector<GridNode>>(dimensions.y);
	
	for (int y = 0; y < dimensions.y; ++y) {
		auto& row = _grid[y] = std::vector<GridNode>(dimensions.x);

		for (int x = 0; x < row.size(); ++x) {
			row[x] = GridNode(defaultWeight, {x, y});
		}
	}
}
