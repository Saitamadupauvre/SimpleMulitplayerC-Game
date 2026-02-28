#pragma once

#include "engine/IInput.hpp"
#include "./InputAction.hpp"

#include <unordered_map>
#include <unordered_set>

#include "SDL2/SDL.h"

class InputManager: public IInput
{
public:
    void update();
    bool isActionPressed(InputAction action) const;
    bool isActionJustPressed(InputAction action) const;
    bool shouldQuit() const { return _quit; }

private:
    void processEvent(const SDL_Event& event);

    std::unordered_map<InputAction, SDL_Scancode> _bindings;
    std::unordered_set<SDL_Scancode> _pressed;
    std::unordered_set<SDL_Scancode> _justPressed;
    bool _quit = false;
};
