//
// Created by 11896 on 12/10/2024.
//

#ifndef BLOCKYENGINE_ANIMATEDSPRITE_HPP
#define BLOCKYENGINE_ANIMATEDSPRITE_HPP


#include <vector>
#include <string>
#include <map>
#include "../Renderable.h"
#include "../../Renderer/IRenderer.h"
#include "Animation.hpp"

class AnimatedSprite : public Renderable {
public:
    AnimatedSprite(const char* filePath, IRenderer* renderer, int frameWidth, int frameHeight, int rows, int columns);
    ~AnimatedSprite();

    void update(float deltaTime) override;
    void render(IRenderer* renderer) override;

    void setPosition(int x, int y);
    void addAnimation(const Animation& animation);
    void playAnimation(const std::string& name);
    void stopAnimation();

private:
    SDL_Texture* spritesheet;
    std::vector<SDL_Rect> frames;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    int currentFrame;
    float elapsedTime;
    bool isPlaying;
    SDL_Rect dstRect;

    void updateAnimationFrame();
};


#endif //BLOCKYENGINE_ANIMATEDSPRITE_HPP
