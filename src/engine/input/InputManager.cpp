#include "./InputManager.hpp"

InputManager::InputManager()
{
    static const std::unordered_map<InputAction, std::vector<SDL_Scancode>> defaultBindings = {
        {InputAction::MoveUp, {SDL_SCANCODE_W, SDL_SCANCODE_SPACE, SDL_SCANCODE_UP}},
        {InputAction::MoveDown, {SDL_SCANCODE_S, SDL_SCANCODE_DOWN}},
        {InputAction::MoveLeft, {SDL_SCANCODE_A, SDL_SCANCODE_LEFT}},
        {InputAction::MoveRight, {SDL_SCANCODE_D, SDL_SCANCODE_RIGHT}},
    };

    _bindings = defaultBindings;
}

void InputManager::clearTransientInputs()
{
    _justPressed.clear();
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

    for (const SDL_Scancode scancode : it->second) {
        if (_pressed.contains(scancode)) {
            return true;
        }
    }
    return false;
}

bool InputManager::isActionJustPressed(InputAction action) const
{
    auto it = _bindings.find(action);
    if (it == _bindings.end())
        return false;

    for (const SDL_Scancode scancode : it->second) {
        if (_justPressed.contains(scancode)) {
            return true;
        }
    }
    return false;
}
