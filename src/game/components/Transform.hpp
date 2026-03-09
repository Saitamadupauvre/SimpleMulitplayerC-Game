#pragma once

#include "engine/Component.hpp"
#include "engine/IRenderer.hpp"

struct Transform : Component {
    Vec2 position;
    float rotation = 0;
    Vec2 scale{1, 1};
};
