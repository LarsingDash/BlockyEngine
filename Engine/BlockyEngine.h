#pragma once

#include "WindowModule.h"
#include "InputModule.h"
#include "Renderer/IRenderer.h"
#include "Renderer/RenderableManager.h"
#include "Renderable/Shapes/Circle.h"
#include "Renderable/Shapes/Rectangle.h"
class BlockyEngine {
public:
    BlockyEngine(bool useHardware);
    ~BlockyEngine();
    void run();
    RenderableManager renderManager;

private:
    void processEvents();

    bool shouldQuit;
    WindowModule* windowModule;
    IRenderer* renderer;
    InputModule* inputModule;
};
