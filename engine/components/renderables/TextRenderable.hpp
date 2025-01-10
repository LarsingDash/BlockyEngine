//
// Created by 11896 on 06/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_TEXTRENDERABLE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_TEXTRENDERABLE_HPP_

#include <utility>

#include "Renderable.hpp"
#include "SDL_ttf.h"
#include "utilities/JsonUtil.hpp"

class TextRenderable : public Renderable {
	public:
		TextRenderable(GameObject* gameObject, const char* tag,
					   std::string text, const glm::ivec4& color,
					   std::string fontPath, int fontSize, int layer = 0
		);
		~TextRenderable() override;

		void SetText(const std::string& newText);
		[[nodiscard]] const std::string& GetText() const;
		[[nodiscard]] const glm::ivec4& GetColor() const;
		[[nodiscard]] TTF_Font* GetFont() const;

		JSON_REGISTER_HEADER(TextRenderable)

	private:
		std::string _text;
		glm::ivec4 _color;

		std::string _fontPath;
		int _fontSize;
		TTF_Font* _font{nullptr};
		
		Component* _clone(const GameObject& parent) override;
};

JSON_REGISTER_COMPONENT(TextRenderable)

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_TEXTRENDERABLE_HPP_
