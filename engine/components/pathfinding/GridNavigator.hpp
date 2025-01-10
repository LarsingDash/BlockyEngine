//
// Created by larsv on 28/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_PATHFINDING_GRIDNAVIGATOR_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_PATHFINDING_GRIDNAVIGATOR_HPP_

#include "components/Component.hpp"
#include "components/pathfinding/PathfindingGrid.hpp"

class GridNavigator : public Component {
	public:
		GridNavigator(GameObject* gameObject, const char* tag, const char* gridTag,
					  glm::ivec2 startingGridPos, float movementSpeed = 1.f);
		~GridNavigator() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void SetTarget(const glm::vec2& worldPos);

	private:
		std::string _gridTag;
		glm::ivec2 _startingGridPos;

		float _movementSpeed;
		float _elapsedTime{0.f};
		PathfindingGrid::Node* _currentNode{nullptr};
		int _pathIndex{1};
		std::vector<PathfindingGrid::Node*> _path{};

		PathfindingGrid* _grid{nullptr};

		Component* _clone(const GameObject& parent) override;
};
#endif //BLOCKYENGINE_ENGINE_COMPONENTS_PATHFINDING_GRIDNAVIGATOR_HPP_
