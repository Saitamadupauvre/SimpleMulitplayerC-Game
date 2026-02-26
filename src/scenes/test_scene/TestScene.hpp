#pragma once

#include "core/IScene.hpp"
#include <SDL2/SDL.h>

class TestScene : public IScene
{
public:
    TestScene();

    void onEvent(const SDL_Event& event) override;
    void onUpdate(double dt) override;
    void onRender(SDL_Renderer& renderer, double alpha) override;

private:
    float _x = 100.0f;
    float _y = 100.0f;
    float _prevX = 100.0f;
    float _prevY = 100.0f;
    float _speed = 200.0f;
};