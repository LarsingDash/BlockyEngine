//
// Created by larsv on 24/09/2024.
//

#ifndef BLOCKYENGINE_EXAMPLECOMPONENT_H
#define BLOCKYENGINE_EXAMPLECOMPONENT_H

#include "Component.h"
#include "SDL_rect.h"

class ExampleComponent : public Component {
	public:
		ExampleComponent(int x, int y, int greyScale);
		ExampleComponent() : ExampleComponent(0,0, 0){};
		void OnUpdate(float delta) override;
		~ExampleComponent() override;
	private:
		SDL_Rect* rect;
		int greyScale;
};


#endif //BLOCKYENGINE_EXAMPLECOMPONENT_H
