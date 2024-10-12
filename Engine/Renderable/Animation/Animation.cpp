//
// Created by 11896 on 12/10/2024.
//

#include "Animation.hpp"

Animation::Animation(const std::string& name, int startFrame, int endFrame, float frameTime, bool looping)
        : name(name), startFrame(startFrame), endFrame(endFrame), frameTime(frameTime), looping(looping) {}
