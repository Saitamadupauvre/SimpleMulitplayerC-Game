#pragma once

#include <set>

#include "Entity.hpp"

#include "engine/Signature.hpp"
#include "engine/IRenderer.hpp"

class System
{
public:
    virtual ~System() = default;

    virtual void update(class World& world, float dt) = 0;
    virtual void render(World& world, IRenderer& renderer, double alpha) = 0;

    virtual Signature getSignature() const = 0;

    std::set<Entity> entities;
};
