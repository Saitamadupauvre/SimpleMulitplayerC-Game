#pragma once

#include "engine/core/Component.hpp"
#include "engine/core/Types.hpp"

struct Sprite : Component {
    TextureID texture = 0;
    int width = 1;
    int height = 1;
};
