#include "./TestScene.hpp"

void TestScene::onEvent(const SDL_Event& event)
{
}

void TestScene::onUpdate(double dt)
{
    _prevX = _x;
    _prevY = _y;

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_UP])    _y -= _speed * dt;
    if (state[SDL_SCANCODE_DOWN])  _y += _speed * dt;
    if (state[SDL_SCANCODE_LEFT])  _x -= _speed * dt;
    if (state[SDL_SCANCODE_RIGHT]) _x += _speed * dt;

    if (_x < 0) _x = 0;
    if (_y < 0) _y = 0;
    if (_x > 800 - 32) _x = 800 - 32;
    if (_y > 600 - 32) _y = 600 - 32;
}

void TestScene::onRender(SDL_Renderer& renderer, double alpha)
{
    float renderX = _prevX + (_x - _prevX) * static_cast<float>(alpha);
    float renderY = _prevY + (_y - _prevY) * static_cast<float>(alpha);

    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
    SDL_RenderClear(&renderer);

    SDL_Rect rect {
        static_cast<int>(renderX),
        static_cast<int>(renderY),
        32, 32
    };
    SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(&renderer, &rect);

    SDL_RenderPresent(&renderer);
}