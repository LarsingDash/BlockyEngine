//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_SPRITERENDERABLE_HPP
#define BLOCKYENGINE_SPRITERENDERABLE_HPP

#include "Renderable.hpp"

class SpriteRenderable : public Renderable {
	public:
		SpriteRenderable(GameObject* gameObject, const char* tag,
						 std::string filePath, std::string spriteTag,
						 RenderableType type = RenderableType::SPRITE, int layer = 0);
		~SpriteRenderable() override = default;
		
		[[nodiscard]] std::string GetFilePath() const;
		[[nodiscard]] std::string GetSpriteTag() const;

	private:
		Component* _clone(const GameObject& parent) override;
		
		std::string _spriteTag;
		std::string _filePath;
};

#endif //BLOCKYENGINE_SPRITERENDERABLE_HPP
