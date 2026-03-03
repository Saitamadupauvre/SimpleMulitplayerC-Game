#pragma once

#include "engine/Component.hpp"

struct Transform : Component {
    float x = 0;
    float y = 0;
    float rotation = 0;
    float scaleX = 1;
    float scaleY = 1;
};
