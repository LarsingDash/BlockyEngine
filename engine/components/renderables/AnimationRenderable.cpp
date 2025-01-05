#include "AnimationRenderable.hpp"

#include <sstream>

#include <stb_image/stb_image.h>

#include "gameObject/GameObject.hpp"
#include "logging/BLogger.hpp"

AnimationRenderable::AnimationRenderable(GameObject* gameObject, const char* tag,
										 std::string filePath, std::string spriteTag,
										 int frameWidth, int frameHeight, int layer, SpriteFlip spriteFlip)
		: SpriteRenderable(gameObject, tag, std::move(filePath), std::move(spriteTag),
						   RenderableType::ANIMATED, layer, spriteFlip) {

	_frameWidth = frameWidth;
	_frameHeight = frameHeight;

	if (GetFilePath().empty()) {
		throw std::invalid_argument("File path for animation cannot be empty.");
	}
	_loadFrames();
}

Component* AnimationRenderable::_clone(const GameObject& parent) {
	auto clone = new AnimationRenderable(*this);
	return clone;
}

//Gets the image, checks pixels parameters and divides the spritesheet into _frames adding them to a vector
void AnimationRenderable::_loadFrames() {
	int channels;

	const std::string& filePath = GetFilePath();
	unsigned char* imageData = stbi_load(filePath.c_str(), &_sheetWidth, &_sheetHeight, &channels, 0);
	if (!imageData) {
		std::string err("Failed to load texture sheet: ");
		err += filePath;
		BLOCKY_ENGINE_ERROR(err);
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

	std::stringstream msg{};
	msg << "Loaded ";
	msg << std::string();
	msg << " _frames from texture sheet: ";
	msg << filePath;
	BLOCKY_ENGINE_DEBUG(msg.str());
}

//Returns the source rect (current frame)
const glm::ivec4* AnimationRenderable::GetSourceRect() const {
	return &_sourceRect;
}

//Returns frame by index
const glm::ivec4& AnimationRenderable::GetFrame(int index) const {
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

JSON_REGISTER_FROM_CUSTOM(
		AnimationRenderable,
		[](const nlohmann::json& json, AnimationRenderable& other) {
			auto jsonVec4 = ([](const nlohmann::json& json) {
				return glm::ivec4{
						json.at("x").get<int>(),
						json.at("y").get<int>(),
						json.at("z").get<int>(),
						json.at("w").get<int>()
				};
			});

			other._sourceRect = jsonVec4(json.at("sourceRect"));
		},
		json.at("spritePath").get<std::string>(),
		json.at("spriteTag").get<std::string>(),
		json.at("frameWidth").get<int>(),
		json.at("frameHeight").get<int>(),
		json.at("layer").get<int>(),
		json.at("spriteFlip").get<SpriteFlip>()
)

JSON_REGISTER_TO(
		AnimationRenderable,
		[](nlohmann::json& json, const AnimationRenderable& other) {
			json["layer"] = other.GetLayer();
			json["frameWidth"] = other._frameWidth;
			json["frameHeight"] = other._frameHeight;
			json["spritePath"] = other._filePath;
			json["spriteTag"] = other._spriteTag;
			json["spriteFlip"] = other._spriteFlip;

			auto jsonVec4 = [](const glm::ivec4& rect) {
				return (nlohmann::json{
						{"x", rect.x},
						{"y", rect.y},
						{"z", rect.z},
						{"w", rect.w}
				});
			};
			json["sourceRect"] = jsonVec4(other._sourceRect);
		}
)
