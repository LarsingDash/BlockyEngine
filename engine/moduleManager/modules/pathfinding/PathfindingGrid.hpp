//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_

#include <string>
#include <vector>
#include <memory>

#include "GridNode.hpp"

class RenderingModule;

class PathfindingGrid {
	public:
		PathfindingGrid() = delete;
		PathfindingGrid(const char* tag, int defaultWeight, glm::ivec2 dimensions);
		~PathfindingGrid() = default;

		void Visualize(bool show);

		inline GridNode& operator()(int x, int y) { return _grid[y][x]; }

	private:
		std::string _tag;
		RenderingModule& _renderingModule;
		
		glm::ivec2 _dimensions;
		std::vector<std::vector<GridNode>> _grid;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
