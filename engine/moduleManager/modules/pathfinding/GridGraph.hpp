//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_GRIDGRAPH_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_GRIDGRAPH_HPP_

#include <vector>
#include <memory>

#include "GridNode.hpp"

class GridGraph {
	public:
		GridGraph() = delete;
		GridGraph(int defaultWeight, glm::ivec2 dimensions);
		~GridGraph() = default;

		inline GridNode& operator()(int x, int y) { return _grid[y][x]; }

	private:
		glm::ivec2 _dimensions;
		std::vector<std::vector<GridNode>> _grid;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_GRIDGRAPH_HPP_
