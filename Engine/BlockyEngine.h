#pragma once

#include "WindowModule.h"
#include "RenderingModule.h"
#include "InputModule.h"

class BlockyEngine {
public:
    BlockyEngine();
    ~BlockyEngine();
    void run();

private:
    void processEvents();

    bool shouldQuit;
    WindowModule* windowModule;
    RenderingModule* renderingModule;
    InputModule* inputModule;
};
