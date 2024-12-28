//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_

#include <string>
#include <vector>
#include <memory>

#include "GridNode.hpp"
#include "components/Component.hpp"

class RenderingModule;

class PathfindingGrid : public Component {
	public:
		PathfindingGrid(GameObject* gameObject, const char* tag, int defaultWeight, glm::ivec2 dimensions, bool visualize);
		~PathfindingGrid() override = default;

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void Visualize(bool show);
		inline void SetVisualizationOpacity(int opacity) { _opacity = opacity; }

		inline GridNode& operator()(int x, int y) { return _grid[y][x]; }

	private:
		RenderingModule& _renderingModule;
		
		bool _shouldVisualize;
		int _opacity{255};
		
		glm::ivec2 _dimensions;

		std::vector<std::vector<GridNode>> _grid;

		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
