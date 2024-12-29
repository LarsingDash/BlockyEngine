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

constexpr int NonWalkableIndex = 0;
constexpr int VisitedIndex = -1;
constexpr int PathIndex = -2;

class PathfindingGrid : public Component {
	public:
		enum NodeStatus {
			Normal,
			Visited,
			Path
		};
		struct Node {
			bool IsWalkable;
			NodeStatus status;
			int Weight;
			glm::ivec2 GridPos;
			glm::vec2 WorldPos;
		};

		PathfindingGrid(GameObject* gameObject, const char* tag, int defaultWeight, glm::ivec2 dimensions);
		~PathfindingGrid() override;

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void RefreshGridPositions();
		void SetWeightsFromText(const std::string& text);

		Node& GetClosestNodeTo(const glm::vec2& worldPos);
		void SetNodeStatus(Node& node, NodeStatus status);
		std::vector<Node*> AStarPathfinding(Node& start, Node& target);

		inline void SetVisualization(bool visualize) { _shouldVisualize = visualize; }
		inline void SetVisualizationOpacity(int opacity) { _opacity = opacity; }
		inline void SetNodeSize(float size) { _nodeSize = size; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArrayIndexOutOfBounds"
//The special colors can be in the negatives since 0 or negative weights don't work for pathfinding anyway...
//However, Clang is seeing this as an issue since negative indices in [...] are normally problematic
		inline void SetNonWalkableColor(const glm::ivec3& color) { _colors[NonWalkableIndex] = color; }
		inline void SetVisitedColor(const glm::ivec3& color) { _colors[VisitedIndex] = color; }
		inline void SetPathColor(const glm::ivec3& color) { _colors[PathIndex] = color; }
#pragma clang diagnostic pop
		inline void SetWeightColor(int weight, const glm::ivec3& color) { _colors[weight] = color; }

		inline const glm::ivec2& GetDimensions() const { return _dimensions; }

		inline Node& operator()(int x, int y) { return _nodes[y][x]; }

		static PathfindingGrid* GetGridByTag(const std::string& tag);

	private:
		void _visualize(bool show);

		RenderingModule& _renderingModule;

		bool _shouldVisualize{false};
		int _opacity{255};
		float _nodeSize{50.f};

		glm::ivec2 _dimensions;
		std::unordered_map<int, glm::ivec3> _colors;
		std::vector<std::vector<Node>> _nodes;

		static std::unordered_map<std::string, PathfindingGrid*> _grids;

		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGGRID_HPP_
