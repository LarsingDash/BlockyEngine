//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_GRIDNODE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_GRIDNODE_HPP_

#include "dependencies/glm/vec2.hpp"

class GridNode {
	public:
		GridNode() = default;
		GridNode(int weight, glm::ivec2 gridPos);
		~GridNode() = default;

		inline void SetWalkable(bool isWalkable) { _isWalkable = isWalkable; }
		inline void SetWeight(int weight) { _weight = weight; }

	private:
		friend class PathfindingGrid;
		bool _isWalkable;
		int _weight;
		glm::ivec2 _gridPos;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_GRIDNODE_HPP_
