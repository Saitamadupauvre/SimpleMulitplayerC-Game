#pragma once

#include "engine/core/Component.hpp"

enum class ColliderType {
    Solid,
    OneWayPlatform,
};

struct Collider : Component {
    float width = 0.0f;
    float height = 0.0f;
    ColliderType type = ColliderType::Solid;
};
