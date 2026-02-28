#pragma once

#include "engine/IScene.hpp"
#include <SDL2/SDL.h>

#include "../../../engine/ecs/World.hpp"

class TestScene : public IScene
{
public:
    TestScene();

    void onEvent(const SDL_Event& event) override;
    void onUpdate(const IInput& inputManager, double dt) override;
    void onRender(SDL_Renderer& renderer, double alpha) override;

private:
    World _world;
};
