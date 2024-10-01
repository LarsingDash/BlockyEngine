//
// Created by larsv on 01/10/2024.
//

#ifndef BLOCKYENGINE_TRANSEXAMPLECOMPONENT_HPP
#define BLOCKYENGINE_TRANSEXAMPLECOMPONENT_HPP

#include "Component.hpp"
#include "../GameObject/Transform.hpp"
#include "../GameObject/GameObject.hpp"
#include "SDL_render.h"

class TransExampleComponent : public Component {
	public:
		TransExampleComponent(GameObject& gameObject, Transform& transform);
		void OnUpdate(float delta) override;
		~TransExampleComponent() override;
		
	private:
		SDL_Texture* texture;
		SDL_FRect* rect;
};


#endif //BLOCKYENGINE_TRANSEXAMPLECOMPONENT_HPP
