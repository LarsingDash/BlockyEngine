//
// Created by larsv on 01/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_MOUSEREPARENTING_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_MOUSEREPARENTING_HPP_

#include "components/Component.hpp"

class MouseReparenting : public Component {
	public:
		MouseReparenting(GameObject& parent, const char* tag, GameObject& parentA, GameObject& parentB);

		void Start() override;
		void Update(float delta) override;
		void End() override;
		
	private:
		GameObject& parentA;
		GameObject& parentB;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_MOUSEREPARENTING_HPP_
