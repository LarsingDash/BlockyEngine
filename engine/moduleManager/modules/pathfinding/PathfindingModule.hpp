//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGMODULE_HPP_

#include <memory>

#include "moduleManager/ModuleWrapper.hpp"
#include "moduleManager/modules/pathfinding/GridGraph.hpp"

class PathfindingModule : public ModuleWrapper {
	public:
		PathfindingModule();
		~PathfindingModule() override = default;

		void Update(float delta) override;

		template<typename ... Args>
		[[nodiscard]] GridGraph& SetGrid(Args&& ...args) {
			_graph = std::make_unique<GridGraph>(std::forward<Args>(args)...);
			return *_graph;
		}

	private:
		std::unique_ptr<GridGraph> _graph;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGMODULE_HPP_
