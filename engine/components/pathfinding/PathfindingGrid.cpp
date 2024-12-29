//
// Created by larsv on 27/12/2024.
//

#include "PathfindingGrid.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

std::unordered_map<std::string, PathfindingGrid*> PathfindingGrid::_grids{};

PathfindingGrid::PathfindingGrid(
		GameObject* gameObject, const char* tag,
		int defaultWeight, glm::ivec2 dimensions) :
		Component(gameObject, tag, true),
		_renderingModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule()),
		_dimensions(dimensions), _nodes() {
	//Colors
	_colors[NonWalkableIndex] = {200, 0, 0};
	_colors[VisitedIndex] = {0, 100, 0};
	_colors[PathIndex] = {0, 250, 0};
	_colors[defaultWeight] = {200, 200, 200};

	//Grid initialization
	_nodes = std::vector<std::vector<Node>>(dimensions.y);
	for (int y = 0; y < dimensions.y; ++y) {
		auto& row = _nodes[y] = std::vector<Node>(dimensions.x);
		for (int x = 0; x < row.size(); ++x) {
			row[x] = Node{
					.IsWalkable = true,
					.status = NodeStatus::Normal,
					.Weight = defaultWeight,
					.GridPos = {x, y},
					.WorldPos = {},
			};
		}
	}
}

PathfindingGrid::~PathfindingGrid() = default;

void PathfindingGrid::Start() {
	RefreshGridPositions();

	_visualize(_shouldVisualize);
	_grids[tag] = this;
}

void PathfindingGrid::Update(float delta) {}

void PathfindingGrid::End() {
	_visualize(false);
	_grids.erase(tag);
}

void PathfindingGrid::RefreshGridPositions() {
	auto& pos = componentTransform->GetWorldPosition();
	auto& scale = componentTransform->GetWorldScale();
	auto halfScale = scale / 2.f;

	float xStep = scale.x / static_cast<float>(_dimensions.x - 1);
	float yStep = scale.y / static_cast<float>(_dimensions.y - 1);

	for (auto& row : _nodes) {
		for (auto& node : row) {
			node.WorldPos = {
					xStep * static_cast<float>(node.GridPos.x) - halfScale.x + pos.x,
					yStep * static_cast<float>(node.GridPos.y) - halfScale.y + pos.y
			};
		}
	}
}

void PathfindingGrid::SetWeightsFromText(const std::string& text) {
	std::vector<std::string> lines;

	int counter{0};
	std::string temp;

	for (char c : text) {
		if (c == '\n') {
			++counter;
			lines.emplace_back(temp.c_str());
			temp.clear();
		} else temp += c;
	}

	for (int y = 0; y < std::min(lines.size(), _nodes.size()); ++y) {
		auto& row = _nodes[y];
		auto& line = lines[y];

		for (int x = 0; x < std::min(line.length(), row.size()); ++x) {
			char weight = line[x];
			if (weight == 'N') row[x].IsWalkable = false;
			else row[x].Weight = weight - '0';
		}
	}
}

PathfindingGrid::Node& PathfindingGrid::GetClosestNodeTo(const glm::vec2& worldPos) {
	//Transform world coords to float values where the top-left node is {0.f, 0.f} and bottom-right is {1.f, 1.f}
	auto indexRaw =
			(worldPos - componentTransform->GetWorldPosition()) //Position to the grid
					/ componentTransform->GetWorldScale() //Scale to the grid size
					+ glm::vec2{0.5f}; //Offset to get 0 to 1

	//Scale to grid dimensions. IndexRaw now goes from {0.f, 0.f} to {_dimensions.x, _dimensions.y}
	indexRaw.x *= static_cast<float>(_dimensions.x - 1);
	indexRaw.y *= static_cast<float>(_dimensions.y - 1);

	//Return the node, cast from the indices, clamped between the bounds of the grid
	return _nodes
	[std::max(0, std::min(static_cast<int>(std::round(indexRaw.y)), _dimensions.y - 1))]
	[std::max(0, std::min(static_cast<int>(std::round(indexRaw.x)), _dimensions.x - 1))];
}

void PathfindingGrid::SetNodeStatus(PathfindingGrid::Node& node, PathfindingGrid::NodeStatus status) {
	if (node.status == status) return;
	node.status = status;

	std::string name{tag + std::to_string(node.GridPos.x) + ',' + std::to_string(node.GridPos.y) + "Status"};
	if (status == NodeStatus::Normal)
		_renderingModule.RemoveDebugRectangle(name);
	else
		_renderingModule.AddDebugRectangle(
				name,
				[&node, &colors = _colors, &opacity = _opacity, &nodeSize = _nodeSize]
						(glm::vec2& position, glm::vec2& size, glm::ivec4& color) {
					position = node.WorldPos;
					size.x = size.y = nodeSize / 2.f;

					switch (node.status) {
						default:
							break;
						case Visited:
							color = {colors[VisitedIndex], opacity};
							break;
						case Path:
							color = {colors[PathIndex], opacity};
							break;
					}
				}, 1);
}

std::vector<PathfindingGrid::Node*> PathfindingGrid::AStarPathfinding(PathfindingGrid::Node& start,
																	  PathfindingGrid::Node& target) {
	return {};
}

PathfindingGrid* PathfindingGrid::GetGridByTag(const std::string& tag) {
	auto it = _grids.find(tag);
	return (it != _grids.end()) ? _grids.at(tag) : nullptr;
}

void PathfindingGrid::_visualize(bool show) {
	for (auto& row : _nodes) {
		for (auto& node : row) {
			std::string name{tag + std::to_string(node.GridPos.x) + ',' + std::to_string(node.GridPos.y)};

			if (show)
				_renderingModule.AddDebugRectangle(
						name,
						[&node, &colors = _colors, &opacity = _opacity, &nodeSize = _nodeSize]
								(glm::vec2& position,
								 glm::vec2& size,
								 glm::ivec4& color) {
							position = node.WorldPos;
							size.x = size.y = nodeSize;

							if (!node.IsWalkable) color = {colors[0], opacity};
							else color = {colors[node.Weight], opacity};
						});
			else {
				_renderingModule.RemoveDebugRectangle(name);
				SetNodeStatus(node, NodeStatus::Normal);
			}
		}
	}
}

Component* PathfindingGrid::_clone(const GameObject& parent) {
	auto clone = new PathfindingGrid(*this);
	return clone;
}
