//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RENDERINGMODULE_HPP
#define BLOCKYENGINE_RENDERINGMODULE_HPP

#include <unordered_map>

#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/AnimationRenderable.hpp"
#include <SDL_render.h>

class RenderingModule {
	public:
		explicit RenderingModule(SDL_Renderer* renderer);
		~RenderingModule();

		void Render();
		void AddRenderable(Renderable& renderable);
		void RemoveRenderable(Renderable& renderable);

	private:
		SDL_Renderer* _renderer;
		std::vector<std::reference_wrapper<Renderable>> renderables;
		std::unordered_map<std::string, std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>> _textureCache;

		void _renderRectangle(RectangleRenderable& renderable);
		void _renderEllipse(EllipseRenderable& renderable);
		void _renderSprite(SpriteRenderable& renderable);
		void _renderAnimatedSprite(AnimationRenderable& renderable);
		void _renderTexture(SDL_Texture* texture, const ComponentTransform& transform, const glm::ivec4* sourceRect);
		SDL_Texture* _loadTexture(const SpriteRenderable& sprite, int& width, int& height);
};

#endif //BLOCKYENGINE_RENDERINGMODULE_HPP
