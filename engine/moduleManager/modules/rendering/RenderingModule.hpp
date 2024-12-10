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
#include "components/renderables/AnimationRenderable.hpp"
#include "components/renderables/TextRenderable.hpp"
#include "utilities/TimeUtil.hpp"

class RenderingModule {
	public:
		explicit RenderingModule(SDL_Renderer* renderer);
		~RenderingModule();

		void Render();
		void AddRenderable(Renderable& renderable);
		void RemoveRenderable(Renderable& renderable);

	private:
		SDL_Renderer* _renderer;
		std::vector<std::reference_wrapper<Renderable>> _renderables;
		std::unordered_map<std::string, std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>> _textureCache;
		TTF_Font* _font;

		void _renderRectangle(RectangleRenderable& renderable);
		void _renderEllipse(EllipseRenderable& renderable);
		void _renderSprite(SpriteRenderable& renderable);
		void _renderAnimatedSprite(AnimationRenderable& renderable);
		void _renderTexture(SDL_Texture* texture, const ComponentTransform& transform, const glm::ivec4* sourceRect);
		void _renderText(TextRenderable& renderable);
		void _renderTextHelper(const std::string& text, const SDL_Color& color, const SDL_FPoint& position);
		void _renderGameInfo();
		SDL_Texture* _loadTexture(const SpriteRenderable& sprite, int& width, int& height);
};

#endif //BLOCKYENGINE_RENDERINGMODULE_HPP
