//
// Created by larsv on 13/11/2024.
//

#ifndef BLOCKYENGINE_RENDERABLE_HPP
#define BLOCKYENGINE_RENDERABLE_HPP

#include "Component.hpp"

class Renderable : public Component {
	public:
		Renderable(GameObject& gameObject, const char* tag);
		~Renderable() override;
		
		void Start() override;
		void Update(float delta) override;
		void End() override;
};


#endif //BLOCKYENGINE_RENDERABLE_HPP