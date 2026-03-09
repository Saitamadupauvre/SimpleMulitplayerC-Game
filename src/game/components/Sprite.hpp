#pragma once

#include "engine/Component.hpp"
#include <cstdint>

using TextureID = std::uint32_t;

struct Sprite : Component {
    TextureID texture = 0;
    int width = 1;
    int height = 1;
};
