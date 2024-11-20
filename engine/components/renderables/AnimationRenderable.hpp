//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_

#include <string>
#include <vector>
#include "SpriteRenderable.hpp"
#include "SDL_rect.h"

class AnimationRenderable : public SpriteRenderable {
	public:
		AnimationRenderable(GameObject& gameObject, const char* tag, std::string filePath,
							std::string spriteTag, int frameWidth, int frameHeight);

		void LoadFrames(int sheetWidth, int sheetHeight);

		[[nodiscard]] const SDL_Rect* GetSourceRect() const override;

		const SDL_Rect& GetFrame(int index) const;

		SDL_Rect sourceRect{};
	private:
		int frameWidth, frameHeight;
		int sheetWidth{}, sheetHeight{};

		std::vector<SDL_Rect> frames;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_RENDERABLES_ANIMATIONRENDERABLE_HPP_
