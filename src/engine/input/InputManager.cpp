#include "./InputManager.hpp"

void InputManager::update()
{
    _justPressed.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        processEvent(event);
    }
}

void InputManager::processEvent(const SDL_Event& event)
{
    if (event.type == SDL_QUIT) {
        _quit = true;
    }

    if (event.type == SDL_KEYDOWN && !event.key.repeat) {
        _pressed.insert(event.key.keysym.scancode);
        _justPressed.insert(event.key.keysym.scancode);
    }

    if (event.type == SDL_KEYUP) {
        _pressed.erase(event.key.keysym.scancode);
    }
}

bool InputManager::isActionPressed(InputAction action) const
{
    auto it = _bindings.find(action);
    if (it == _bindings.end())
        return false;

    return _pressed.contains(it->second);
}

bool InputManager::isActionJustPressed(InputAction action) const
{
    auto it = _bindings.find(action);
    if (it == _bindings.end())
        return false;

    return _justPressed.contains(it->second);
}
