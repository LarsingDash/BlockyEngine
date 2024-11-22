//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
#include <string>
#include <vector>
#include <iostream>
#include <glm/vec4.hpp>
#include "SpriteRenderable.hpp"

class AnimationRenderable : public SpriteRenderable {
	public:
		AnimationRenderable(GameObject& gameObject, const char* tag,
							std::string filePath, std::string spriteTag, int frameWidth, int frameHeight);

		[[nodiscard]] const glm::vec4* GetSourceRect() const;
		[[nodiscard]] const glm::vec4& GetFrame(int index) const;
		void SetCurrentFrame(int frameIndex);

	private:
		void _loadFrames();
		int _frameWidth{}, _frameHeight{};
		int _sheetWidth{}, _sheetHeight{};
		std::vector<glm::vec4> _frames;
		glm::vec4 _sourceRect{};

};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
