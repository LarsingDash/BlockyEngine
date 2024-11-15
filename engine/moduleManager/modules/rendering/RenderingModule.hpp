//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RENDERINGMODULE_HPP
#define BLOCKYENGINE_RENDERINGMODULE_HPP


#include <vector>
#include "SDL_render.h"
#include "components/renderables/Renderable.hpp"

class RenderingModule {
public:
    explicit RenderingModule(SDL_Renderer *renderer);
    ~RenderingModule() = default;
    void Render(const std::vector<std::reference_wrapper<Renderable>>& renderables);

private:
    SDL_Renderer *renderer;

    void RenderRectangle(Renderable &renderable);
    void RenderEllipse(Renderable &renderable);
    void RenderSprite(Renderable &renderable);
};


#endif //BLOCKYENGINE_RENDERINGMODULE_HPP
