#pragma once

#include <SDL2/SDL.h>
#include "./IInput.hpp"

#include "engine/IRenderer.hpp"

class IScene
{
public:
    virtual ~IScene() = default;

    virtual void onEvent(const SDL_Event& event) = 0;
    virtual void onUpdate(const IInput& inputManager, double dt) = 0;
    virtual void onRender(IRenderer& renderer, double alpha) = 0;
};
