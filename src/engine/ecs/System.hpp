#pragma once

#include <set>

#include "Entity.hpp"

class System
{
public:
    virtual ~System() = default;

    virtual void update(class World& world, float dt) = 0;

    std::set<Entity> entities;
};
