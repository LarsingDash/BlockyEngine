#pragma once

#include "WindowModule.h"
#include "InputModule.h"
#include "IRenderer.h"

class BlockyEngine {
public:
    BlockyEngine(bool useHardware);
    ~BlockyEngine();
    void run();

private:
    void processEvents();

    bool shouldQuit;
    WindowModule* windowModule;
    IRenderer* renderer;
    InputModule* inputModule;
};
