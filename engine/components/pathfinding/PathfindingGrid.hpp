//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "components/Component.hpp"

class RenderingModule;

class PathfindingGrid : public Component {
	public:
		struct Node {
			bool IsWalkable;
			int Weight;
			glm::ivec2 GridPos;
			glm::vec2 WorldPos;
		};

		PathfindingGrid(GameObject* gameObject, const char* tag, int defaultWeight, glm::ivec2 dimensions);
		~PathfindingGrid() override = default;

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void RefreshGridPositions();

		inline void SetVisualization(bool visualize) { _shouldVisualize = visualize; }
		inline void SetVisualizationOpacity(int opacity) { _opacity = opacity; }
		inline void SetNodeSize(float size) { _nodeSize = size; }

		inline void SetNonWalkableColor(const glm::ivec3& color) { _colors[-1] = color; }
		inline void SetWeightColor(int weight, const glm::ivec3& color) { _colors[weight] = color; }

		inline Node& operator()(int x, int y) { return _grid[y][x]; }

	private:
		void _visualize(bool show);

		RenderingModule& _renderingModule;

		bool _shouldVisualize{false};
		int _opacity{255};
		float _nodeSize{50.f};

		glm::ivec2 _dimensions;
		std::unordered_map<int, glm::ivec3> _colors;
		std::vector<std::vector<Node>> _grid;

		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
