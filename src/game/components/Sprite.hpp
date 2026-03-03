#pragma once

#include "engine/Component.hpp"
#include <cstdint>

using TextureID = std::uint32_t;

struct Sprite : Component {
    TextureID texture;
    int width = 1;
    int height = 1;
};
