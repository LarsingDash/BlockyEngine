#include "AnimationRenderable.hpp"
#include "stb_image.h"
#include <iostream>

AnimationRenderable::AnimationRenderable(GameObject& gameObject, const char* tag,
										 std::string filePath, std::string spriteTag, int frameWidth, int frameHeight)
		: SpriteRenderable(gameObject, tag, std::move(filePath), std::move(spriteTag)),
		  frameWidth(frameWidth), frameHeight(frameHeight) {
	if (GetFilePath().empty()) {
		throw std::invalid_argument("File path for animation cannot be empty.");
	}
	LoadFrames();
}

void AnimationRenderable::LoadFrames() {
	int channels;

	const std::string& filePath = GetFilePath();
	unsigned char* imageData = stbi_load(filePath.c_str(), &sheetWidth, &sheetHeight, &channels, 0);
	if (!imageData) {
		std::cerr << "Failed to load texture sheet: " << filePath << std::endl;
		return;
	}

	int columns = sheetWidth / frameWidth;
	int rows = sheetHeight / frameHeight;

	//Split sprite sheet into frames
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			glm::vec4 frame = {
					col * frameWidth,    // x position
					row * frameHeight,   // y position
					frameWidth,          // width
					frameHeight          // height
			};
			frames.push_back(frame);
		}
	}

	//Free image data
	stbi_image_free(imageData);

	std::cout << "Loaded " << frames.size() << " frames from texture sheet: " << filePath << std::endl;
}

const glm::vec4* AnimationRenderable::GetSourceRect() const {
	return &sourceRect;
}

const glm::vec4& AnimationRenderable::GetFrame(int index) const {
	if (index >= 0 && index < frames.size()) {
		return frames[index];
	} else {
		throw std::out_of_range("Frame index out of range");
	}
}
void AnimationRenderable::SetCurrentFrame(int frameIndex) {
	sourceRect = GetFrame(frameIndex);
}
