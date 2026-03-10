#pragma once

#include "engine/core/Component.hpp"
#include "engine/core/Types.hpp"

struct Transform : Component {
    Vec2 position;
    float rotation = 0;
    Vec2 scale{1, 1};
};
