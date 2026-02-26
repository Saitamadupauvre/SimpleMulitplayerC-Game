#pragma once

#include <SDL2/SDL.h>

class IScene
{
public:
    virtual ~IScene() = default;

    virtual void onEvent(const SDL_Event& event) = 0;
    virtual void onUpdate(double dt) = 0;
    virtual void onRender(SDL_Renderer& renderer, double alpha) = 0;
};
