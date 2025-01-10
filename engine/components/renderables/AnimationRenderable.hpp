//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_

#include <string>
#include <vector>
#include <glm/vec4.hpp>

#include "SpriteRenderable.hpp"
#include "utilities/JsonUtil.hpp"

class AnimationRenderable : public SpriteRenderable {
	public:
		AnimationRenderable(GameObject* gameObject, const char* tag,
							std::string filePath, std::string spriteTag,
							int frameWidth, int frameHeight,
							int layer = 0, SpriteFlip spriteFlip = SpriteFlip::FlipNone);

		[[nodiscard]] const glm::ivec4* GetSourceRect() const;
		[[nodiscard]] const glm::ivec4& GetFrame(int index) const;
		void SetCurrentFrame(int frameIndex);

		JSON_REGISTER_HEADER(AnimationRenderable)

	private:
		Component* _clone(const GameObject& parent) override;

		void _loadFrames();
		int _frameWidth{}, _frameHeight{};
		int _sheetWidth{}, _sheetHeight{};
		std::vector<glm::ivec4> _frames;
		glm::ivec4 _sourceRect{};

};

JSON_REGISTER_COMPONENT(AnimationRenderable)

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
