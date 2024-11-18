//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RENDERINGMODULE_HPP
#define BLOCKYENGINE_RENDERINGMODULE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>

#include "components/renderables/Renderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "SDL_render.h"
#include "SDL.h"
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "SDL2_gfx/SDL2_rotozoom.h"

class RenderingModule {
	public:
		explicit RenderingModule(SDL_Renderer* renderer);
		~RenderingModule();
		void Render(const std::vector<std::reference_wrapper<Renderable>>& renderables);

	private:
		SDL_Renderer* renderer;
		std::unordered_map<std::string, std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>> textureCache;

		void RenderRectangle(Renderable& renderable);
		void RenderEllipse(Renderable& renderable);
		void RenderSprite(Renderable& renderable);
		void RenderTexture(SDL_Texture* texture, const ComponentTransform& transform);
		SDL_Texture* LoadTexture(const SpriteRenderable& sprite, int& width, int& height);
};

#endif //BLOCKYENGINE_RENDERINGMODULE_HPP
