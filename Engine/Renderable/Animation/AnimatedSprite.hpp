#ifndef BLOCKYENGINE_ANIMATEDSPRITE_HPP
#define BLOCKYENGINE_ANIMATEDSPRITE_HPP

#include <vector>
#include <string>
#include "../Renderable.h"
#include "../../Renderer/IRenderer.h"
#include "AnimationController.hpp"

class AnimatedSprite : public Renderable {
public:
    AnimatedSprite(const char* filePath, IRenderer* renderer, AnimationController* animationController, int frameWidth, int frameHeight, int desiredWidth, int desiredHeight);
    ~AnimatedSprite();

    void update(float deltaTime) override;
    void render(IRenderer* renderer) override;

    void setPosition(int x, int y);

private:
    SDL_Texture* spritesheet;
    std::vector<SDL_Rect> frames;
    SDL_Rect dstRect;
    AnimationController* animationController;

    void loadFrames(int frameWidth, int frameHeight);
};

#endif // BLOCKYENGINE_ANIMATEDSPRITE_HPP
