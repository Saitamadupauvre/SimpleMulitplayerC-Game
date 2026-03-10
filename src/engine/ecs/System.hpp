#pragma once

#include <algorithm>
#include <vector>

#include "Entity.hpp"

#include "engine/core/Signature.hpp"
#include "engine/render/IRenderer.hpp"

class System
{
public:
    virtual ~System() = default;

    virtual void update(class World& world, float dt) = 0;
    virtual void render(World& world, IRenderer& renderer, double alpha) = 0;

    virtual Signature getSignature() const = 0;

    bool hasEntity(Entity e) const {
        return std::find(entities.begin(), entities.end(), e) != entities.end();
    }

    void addEntity(Entity e) {
        if (!hasEntity(e)) {
            entities.push_back(e);
        }
    }

    void removeEntity(Entity e) {
        entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
    }

    std::vector<Entity> entities;
};
