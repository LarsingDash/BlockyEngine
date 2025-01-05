//
// Created by larsv on 27/12/2024.
//

#include "PathfindingGrid.hpp"

#include <algorithm>
#include <queue>

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
	std::string temp;

	for (char c : text) {
		if (c == '\n') {
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

void PathfindingGrid::ClearGridStatus() {
	for (auto& row : _nodes) {
		for (auto& node : row) SetNodeStatus(node, NodeStatus::Normal);
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

std::vector<PathfindingGrid::Node*> PathfindingGrid::AStarPathfinding(
		PathfindingGrid::Node& start,
		PathfindingGrid::Node& target) {
	ClearGridStatus();

	//Distance from source lookup table
	std::unordered_map<const Node*, int> distances;
	//Temporary path lookup table
	std::unordered_map<Node*, Node*> predecessors;

	//Priority queue
	using nodePair = std::pair<float, Node*>;
	std::priority_queue<
			nodePair,
			std::vector<nodePair>,
			std::greater<>> queue;

	//Prepare Lambda's
	auto heuristic = [&target](const Node* node) {
		//Calculate x and y differences
		auto dx = static_cast<float>(node->GridPos.x - target.GridPos.x);
		auto dy = static_cast<float>(node->GridPos.y - target.GridPos.y);

		//Normalize Euclidean distance by tile size
		return static_cast<float>(std::sqrt(dx * dx + dy * dy));
	};

	auto neighborAction =
			[this, &distances, &predecessors, &queue, &heuristic]
					(Node* curNode, Node* neighbor) {
				if (!neighbor->IsWalkable) return;

				//Get distance and neighbor
				int edgeDistance = distances[curNode] + neighbor->Weight;

				//If the path to this node is closer than current distance, override in lookups and add to queue 
				if (edgeDistance < distances[neighbor]) {
					SetNodeStatus(*neighbor, NodeStatus::Visited);
					distances[neighbor] = edgeDistance;
					predecessors[neighbor] = curNode;
					queue.emplace(static_cast<float>(edgeDistance) + heuristic(neighbor), neighbor);
				}
			};

	//Prepare lookup tables
	for (auto& row : _nodes) {
		for (auto& node : row) {
			//Everything unvisited has max cost
			distances[&node] = std::numeric_limits<int>::max();
			//No connections
			predecessors[&node] = nullptr;
		}
	}

	//Insert start in distance as lowest, and in the queue as first to process 
	distances[&start] = 0;
	queue.emplace(heuristic(&start), &start);

	//Go through all nodes, till all have been processed
	while (!queue.empty()) {
		//Get next nodePair to evaluate
		auto [_, curNode] = queue.top();
		queue.pop();

		//Stop if the target has been found
		auto& curPos = curNode->GridPos;
		if (curPos == target.GridPos) break;

		//Add all neighbors of current node to the lookups and queue
		if (curPos.x > 0) neighborAction(curNode, &_nodes[curPos.y][curPos.x - 1]);
		if (curPos.x < _dimensions.x - 1) neighborAction(curNode, &_nodes[curPos.y][curPos.x + 1]);
		if (curPos.y > 0) neighborAction(curNode, &_nodes[curPos.y - 1][curPos.x]);
		if (curPos.y < _dimensions.y - 1) neighborAction(curNode, &_nodes[curPos.y + 1][curPos.x]);
	}

	//Reconstruct path if target was found
	std::vector<Node*> path;
	for (Node* node = &target; node != nullptr; node = predecessors[node]) {
		path.push_back(node);
		SetNodeStatus(*node, NodeStatus::Path);
	}
	std::reverse(path.begin(), path.end());

	return path;
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
