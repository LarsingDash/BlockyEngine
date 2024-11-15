﻿//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_WINDOWMODULE_HPP
#define BLOCKYENGINE_WINDOWMODULE_HPP

#include <SDL_render.h>

#include <vector>

#include "moduleManager/ModuleWrapper.hpp"
#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"

class WindowModule : public ModuleWrapper {
	public:
		WindowModule();
		~WindowModule() override;

		void Update(float delta) override;

		void AddRenderable(Renderable& renderable);
		void RemoveRenderable(Renderable& renderable);

	private:
		static void ProcessEvents();
		void Render();
        void RenderRectangle(Renderable &renderable);
        void RenderSprite(Renderable &renderable);
        void RenderEllipse(Renderable &renderable);

		constexpr static int WINDOW_WIDTH = 800;
		constexpr static int WINDOW_HEIGHT = 600;

		SDL_Window* window;
		SDL_Renderer* renderer;

		std::vector<std::reference_wrapper<Renderable>> renderables;



};


#endif //BLOCKYENGINE_WINDOWMODULE_HPP