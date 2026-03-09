#pragma once

#include "../System.hpp"

#include "engine/IRenderer.hpp"

class RenderSystem: public System
{
public:
    void update(World& world, float dt) override {}
    void render(World& world, IRenderer& renderer, double alpha) override;

    Signature getSignature() const override;
};
