//
// Created by larsv on 28/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_PATHFINDING_GRIDNAVIGATOR_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_PATHFINDING_GRIDNAVIGATOR_HPP_

#include <components/Component.hpp>

#include "components/pathfinding/PathfindingGrid.hpp"

class GridNavigator : public Component {
	public:
		GridNavigator(GameObject* gameObject, const char* tag, const char* gridTag);
		~GridNavigator() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;

	private:
		std::string _gridTag;

		PathfindingGrid* _grid{nullptr};

		Component* _clone(const GameObject& parent) override;
};
#endif //BLOCKYENGINE_ENGINE_COMPONENTS_PATHFINDING_GRIDNAVIGATOR_HPP_
