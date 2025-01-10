//
// Created by larsv on 29/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_PATHFINDING_MOUSETARGETING_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_PATHFINDING_MOUSETARGETING_HPP_

#include "components/Component.hpp"
#include "GridNavigator.hpp"

class MouseTargetedNavigation : public Component {
	public:
		MouseTargetedNavigation(GameObject* gameObject, const char* tag);
		~MouseTargetedNavigation() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;

	private:
		GridNavigator* _navigator{nullptr};

		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_PATHFINDING_MOUSETARGETING_HPP_
