//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_SPRITERENDERABLE_HPP
#define BLOCKYENGINE_SPRITERENDERABLE_HPP

#include "Renderable.hpp"

#include "utilities/JsonUtil.hpp"

enum SpriteFlip {
	FlipNone,
	FlipHorizontal,
	FlipVertical
};

class SpriteRenderable : public Renderable {
	public:
		SpriteRenderable(GameObject* gameObject, const char* tag,
						 std::string filePath, std::string spriteTag,
						 RenderableType type = RenderableType::SPRITE,
						 int layer = 0, SpriteFlip spriteFlip = SpriteFlip::FlipNone);
		~SpriteRenderable() override = default;

		[[nodiscard]] SpriteFlip GetSpriteFlip() const;
		[[nodiscard]] std::string GetFilePath() const;
		[[nodiscard]] std::string GetSpriteTag() const;

		JSON_REGISTER_HEADER(SpriteRenderable)

	protected:
		SpriteFlip _spriteFlip;
		std::string _spriteTag;
		std::string _filePath;

	private:
		Component* _clone(const GameObject& parent) override;
};

JSON_REGISTER_COMPONENT(SpriteRenderable)

#endif //BLOCKYENGINE_SPRITERENDERABLE_HPP
