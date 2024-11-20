//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_

#include <string>
#include <vector>
#include "SpriteRenderable.hpp"
#include <glm/vec4.hpp>

class AnimationRenderable : public SpriteRenderable {
	public:
		AnimationRenderable(GameObject& gameObject, const char* tag,
							std::string filePath, std::string spriteTag, int frameWidth, int frameHeight);

		[[nodiscard]] const glm::vec4* GetSourceRect() const override;
		[[nodiscard]] const glm::vec4& GetFrame(int index) const;
		void SetCurrentFrame(int frameIndex);

	private:
		void LoadFrames();
		int frameWidth{}, frameHeight{};
		int sheetWidth{}, sheetHeight{};
		std::vector<glm::vec4> frames;
		glm::vec4 sourceRect{};

};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
