//
// Created by 11896 on 06/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_TEXTRENDERABLE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_TEXTRENDERABLE_HPP_

#include "Renderable.hpp"
#include "SDL_ttf.h"

class TextRenderable : public Renderable {
	public:
		TextRenderable(GameObject& gameObject, const char* tag, const std::string& text, const glm::ivec4& color, TTF_Font* font);
		~TextRenderable() override;

		void SetText(const std::string& newText);
		const std::string& GetText() const;
		const glm::ivec4& GetColor() const;
		TTF_Font* GetFont() const;

	private:
		std::string _text;
		glm::ivec4 _color;
		TTF_Font* _font;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_TEXTRENDERABLE_HPP_