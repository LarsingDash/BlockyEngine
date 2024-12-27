//
// Created by larsv on 27/12/2024.
//

#include "PathfindingModule.hpp"
#include <iostream>

PathfindingModule::PathfindingModule() : _graph(nullptr) {}

void PathfindingModule::Update(float delta) {}

void PathfindingModule::SetGrid(GridGraph&& graph) {
	_graph = std::make_unique<GridGraph>(std::move(graph));
}
