//
// Created by larsv on 27/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGMODULE_HPP_

#include <memory>

#include "moduleManager/ModuleWrapper.hpp"
#include "moduleManager/modules/pathfinding/PathfindingGrid.hpp"

class PathfindingModule : public ModuleWrapper {
	public:
		PathfindingModule();
		~PathfindingModule() override = default;

		void Update(float delta) override;

		inline void SetShouldVisualize(bool should) { _grid->Visualize(should); }

		template<typename ... Args>
		[[nodiscard]] PathfindingGrid& SetGrid(Args&& ...args) {
			_grid = std::make_unique<PathfindingGrid>(std::forward<Args>(args)...);
			return *_grid;
		}

	private:
		std::unique_ptr<PathfindingGrid> _grid;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_PATHFINDING_PATHFINDINGMODULE_HPP_
