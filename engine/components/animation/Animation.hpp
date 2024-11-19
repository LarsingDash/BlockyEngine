//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATION_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATION_HPP_

#include <vector>
#include <string>

struct Animation {
	std::string tag;
	bool isLooping;
	std::vector<float> frameBoundingBox;
	std::pair<int, int> animationRange;

	Animation(std::string tag, bool looping, std::pair<int, int> range, std::vector<float> boundingBox)
			: tag(std::move(tag)), isLooping(looping),
			  animationRange(std::move(range)), frameBoundingBox(std::move(boundingBox)) {}
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATION_HPP_
