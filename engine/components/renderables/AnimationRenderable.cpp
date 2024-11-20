//
// Created by 11896 on 19/11/2024.
//

#include "AnimationRenderable.hpp"
#include <iostream>

AnimationRenderable::AnimationRenderable(GameObject& gameObject, const char* tag, std::string filePath,
										 std::string spriteTag, int frameWidth, int frameHeight)
		: SpriteRenderable(gameObject, tag, std::move(filePath), std::move(spriteTag)),
		  frameWidth(frameWidth), frameHeight(frameHeight) {}

void AnimationRenderable::LoadFrames(int width, int height) {
	this->sheetWidth = width;
	this->sheetHeight = height;

	int columns = sheetWidth / frameWidth;
	int rows = sheetHeight / frameHeight;

	// Split sprite into frames
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			SDL_Rect frame = {
					col * frameWidth,
					row * frameHeight,
					frameWidth,
					frameHeight
			};
			frames.push_back(frame);
		}
	}

	std::cout << "Loaded " << frames.size() << " frames from texture sheet." << std::endl;
}

const SDL_Rect* AnimationRenderable::GetSourceRect() const {
	return &sourceRect;
}

const SDL_Rect& AnimationRenderable::GetFrame(int index) const {
	if (index >= 0 && index < frames.size()) {
		return frames[index];
	} else {
		throw std::out_of_range("Frame index out of range");
	}
}

