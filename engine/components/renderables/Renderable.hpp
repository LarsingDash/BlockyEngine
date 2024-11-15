//
// Created by larsv on 13/11/2024.
//

#ifndef BLOCKYENGINE_RENDERABLE_HPP
#define BLOCKYENGINE_RENDERABLE_HPP

#include "components/Component.hpp"

enum RenderableType{
    RECTANGLE,
    ELLIPSE,
    SPRITE
};

class Renderable : public Component {

    public:
		Renderable(GameObject& gameObject, const char* tag, RenderableType renderableType);
        ~Renderable() override;
		
		void Start() override;
		void Update(float delta) override;
		void End() override;
        RenderableType GetRenderableType();

    protected:
        RenderableType _renderableType;

};


#endif //BLOCKYENGINE_RENDERABLE_HPP