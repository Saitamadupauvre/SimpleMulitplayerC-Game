#pragma once

#include "engine/input/IInput.hpp"

#include <unordered_map>
#include <unordered_set>

#include "SDL2/SDL.h"

class InputManager: public IInput
{
public:
    InputManager();

    void beginFrame();
    void processEvent(const SDL_Event& event);
    bool isActionPressed(InputAction action) const;
    bool isActionJustPressed(InputAction action) const;
    bool shouldQuit() const { return _quit; }

private:
    std::unordered_map<InputAction, SDL_Scancode> _bindings;
    std::unordered_set<SDL_Scancode> _pressed;
    std::unordered_set<SDL_Scancode> _justPressed;
    bool _quit = false;
};
