//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATIONCONTROLLER_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATIONCONTROLLER_HPP_

#include "components/renderables/AnimationRenderable.hpp"
#include "utilities/JsonUtil.hpp"

#include <unordered_map>
#include <stdexcept>

class AnimationController : public Component {
	public:
		struct Animation {
			int startFrame;
			int endFrame;
			bool looping;
			float frameDuration;
		};

		AnimationController(GameObject* gameObject, const char* tag);
		~AnimationController() override;
		
		void Start() override;
		void Update(float delta) override;
		void End() override;

		void AddAnimation(const std::string& animationName, int startFrame, int endFrame, float frameDuration, bool looping);
		bool PlayAnimation(const std::string& animationName);
		void StopAnimation();

		JSON_REGISTER_HEADER(AnimationController)

	private:
		Component* _clone(const GameObject& parent) override;
		
		AnimationRenderable* _renderable;
		float _frameTimer = 0.0f;
		int _currentFrame = 0;
		bool _isAnimating = false;

		std::string _currentAnimationName;
		std::unordered_map<std::string, Animation> _animations;
		const Animation* _currentAnimation = nullptr;

		void _updateSourceRect();
};

JSON_REGISTER_COMPONENT(AnimationController)

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATIONCONTROLLER_HPP_
