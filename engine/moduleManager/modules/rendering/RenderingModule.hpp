//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RENDERINGMODULE_HPP
#define BLOCKYENGINE_RENDERINGMODULE_HPP

#include <map>
#include <unordered_map>
#include <functional>

#include <SDL_render.h>

#include "components/renderables/Renderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "components/renderables/AnimationRenderable.hpp"
#include "components/renderables/TextRenderable.hpp"
#include "moduleManager/modules/rendering/Camera.hpp"
#include "utilities/TimeUtil.hpp"


class RenderingModule {
	public:
		explicit RenderingModule(SDL_Renderer* renderer);
		~RenderingModule();

		void Render();
		void AddRenderable(Renderable& renderable);
		void RemoveRenderable(Renderable& renderable);

		using DebugRectangleFunc = std::function<void(glm::vec2& position, glm::vec2& size, glm::ivec4& color)>;
		void AddDebugRectangle(const std::string& tag, DebugRectangleFunc&& function, int layer = 0);
		void RemoveDebugRectangle(const std::string& tag);

		inline Camera& GetCamera() const { return *_camera; }

	private:
		SDL_Renderer* _renderer;
		std::unique_ptr<Camera> _camera;
		std::map<int, std::unordered_map<std::string, DebugRectangleFunc>> _debugRectangles;
		std::map<int, std::vector<std::reference_wrapper<Renderable>>> _renderables;
		std::unordered_map<std::string, std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>> _textureCache;
		TTF_Font* _font;

		void _renderRectangle(RectangleRenderable& renderable);
		void _renderEllipse(EllipseRenderable& renderable);
		void _renderSprite(SpriteRenderable& renderable);
		void _renderAnimatedSprite(AnimationRenderable& renderable);
		void _renderTexture(SDL_Texture* texture,
							const ComponentTransform& transform,
							const glm::ivec4* sourceRect,
							SpriteFlip spriteFlip);
		void _renderText(TextRenderable& renderable);
		void _renderTextHelper(const std::string& text,
							   const SDL_Color& color,
							   const SDL_FPoint& position,
							   float angle = 0.f,
							   bool moveWithCamera = true);
		void _renderGameInfo();
		SDL_Texture* _loadTexture(const SpriteRenderable& sprite, int& width, int& height);

		void _renderDebugRectangles();
};

#endif //BLOCKYENGINE_RENDERINGMODULE_HPP
