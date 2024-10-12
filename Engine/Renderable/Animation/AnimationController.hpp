#ifndef BLOCKYENGINE_ANIMATIONCONTROLLER_HPP
#define BLOCKYENGINE_ANIMATIONCONTROLLER_HPP

#include <string>
#include <unordered_map>
#include "Animation.hpp"

class AnimationController {
public:
    AnimationController();

    void addAnimation(const Animation& animation);
    void playAnimation(const std::string& name);
    void stopAnimation();
    void update(float deltaTime);

    int getCurrentFrame() const;
    bool isAnimationPlaying() const;

private:
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimationName;
    int currentFrame;
    float elapsedTime;
    bool isPlaying;

    void updateAnimationFrame(const Animation& animation);
};

#endif // BLOCKYENGINE_ANIMATIONCONTROLLER_HPP
