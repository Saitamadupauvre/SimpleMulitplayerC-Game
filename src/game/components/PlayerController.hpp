#pragma once

#include "engine/core/Component.hpp"

struct PlayerController : Component {
    float moveSpeed = 240.0f;
    float jumpSpeed = 420.0f;
    float gravity = 980.0f;
    float groundY = 0.0f;
    bool onGround = true;
};
