#pragma once

#include "engine/input/InputAction.hpp"

class IInput
{
public:
    virtual ~IInput() = default;

    virtual bool isActionPressed(InputAction action) const = 0;
    virtual bool isActionJustPressed(InputAction action) const = 0;
};
