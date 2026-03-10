#pragma once

#include "../System.hpp"

#include "engine/render/IRenderer.hpp"

class RenderSystem: public System
{
public:
    void update(World&, float) override {}
    void render(World& world, IRenderer& renderer, double alpha) override;

    Signature getSignature() const override;
};
