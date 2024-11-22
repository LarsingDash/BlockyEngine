#include "AnimationRenderable.hpp"
#include "stb_image.h"

AnimationRenderable::AnimationRenderable(GameObject& gameObject, const char* tag,
										 std::string filePath, std::string spriteTag, int frameWidth, int frameHeight)
		: SpriteRenderable(gameObject, tag, std::move(filePath), std::move(spriteTag)) {
	_renderableType = RenderableType::ANIMATED;

	_frameWidth = frameWidth;
	_frameHeight = frameHeight;

	if (GetFilePath().empty()) {
		throw std::invalid_argument("File path for animation cannot be empty.");
	}
	_loadFrames();
}

//Gets the image, checks pixels parameters and divides the spritesheet into _frames adding them to a vector
void AnimationRenderable::_loadFrames() {
	int channels;

	const std::string& filePath = GetFilePath();
	unsigned char* imageData = stbi_load(filePath.c_str(), &_sheetWidth, &_sheetHeight, &channels, 0);
	if (!imageData) {
		std::cerr << "Failed to load texture sheet: " << filePath << std::endl;
		return;
	}

	int columns = _sheetWidth / _frameWidth;
	int rows = _sheetHeight / _frameHeight;

	//Split sprite sheet into _frames
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			glm::vec4 frame = {
					col * _frameWidth,    // x position
					row * _frameHeight,   // y position
					_frameWidth,          // width
					_frameHeight          // height
			};
			_frames.push_back(frame);
		}
	}

	//Free image data
	stbi_image_free(imageData);

	std::cout << "Loaded " << _frames.size() << " _frames from texture sheet: " << filePath << std::endl;
}


//Returns the source rect (current frame)
const glm::vec4* AnimationRenderable::GetSourceRect() const {
	return &_sourceRect;
}

//Returns frame by index
const glm::vec4& AnimationRenderable::GetFrame(int index) const {
	if (index >= 0 && index < _frames.size()) {
		return _frames[index];
	} else {
		throw std::out_of_range("Frame index out of range");
	}
}

//Sets the current frame
void AnimationRenderable::SetCurrentFrame(int frameIndex) {
	_sourceRect = GetFrame(frameIndex);
}
