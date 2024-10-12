//
// Created by 11896 on 12/10/2024.
//

#ifndef BLOCKYENGINE_ANIMATION_HPP
#define BLOCKYENGINE_ANIMATION_HPP


#include <vector>
#include <string>
#include "SDL_rect.h"

class Animation {
public:
    Animation(const std::string& name, int startFrame, int endFrame, float frameTime, bool looping = true);

    const std::string& getName() const { return name; }
    int getStartFrame() const { return startFrame; }
    int getEndFrame() const { return endFrame; }
    float getFrameTime() const { return frameTime; }
    bool isLooping() const { return looping; }

private:
    std::string name;
    int startFrame;
    int endFrame;
    float frameTime;
    bool looping;
};




#endif //BLOCKYENGINE_ANIMATION_HPP
