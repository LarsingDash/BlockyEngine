#pragma once

#include "WindowModule.h"
#include "InputModule.h"
#include "Renderer/IRenderer.h"
#include "Renderable/RenderManager.h"
#include "Renderable/Circle.h"
#include "Renderable/Rectangle.h"
class BlockyEngine {
public:
    BlockyEngine(bool useHardware);
    ~BlockyEngine();
    void run();
    RenderManager renderManager;

private:
    void processEvents();

    bool shouldQuit;
    WindowModule* windowModule;
    IRenderer* renderer;
    InputModule* inputModule;
};
