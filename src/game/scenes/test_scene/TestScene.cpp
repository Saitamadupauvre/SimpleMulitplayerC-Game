#include "./TestScene.hpp"

TestScene::TestScene()
{
}

void TestScene::onEvent(const SDL_Event& event)
{
}

void TestScene::onUpdate(const IInput& inputManager, double dt)
{
    _prevX = _x;
    _prevY = _y;

    if (inputManager.isActionPressed(InputAction::MoveUp))    _y -= _speed * dt;
    if (inputManager.isActionPressed(InputAction::MoveDown))  _y += _speed * dt;
    if (inputManager.isActionPressed(InputAction::MoveLeft))  _x -= _speed * dt;
    if (inputManager.isActionPressed(InputAction::MoveRight)) _x += _speed * dt;

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
