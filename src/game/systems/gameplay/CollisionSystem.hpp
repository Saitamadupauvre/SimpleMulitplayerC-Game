#pragma once

#include "../System.hpp"

class CollisionSystem : public System
{
public:
    void update(World& world, float dt) override;
    void render(World&, IRenderer&, double) override {}

    Signature getSignature() const override;
};
