#pragma once

#include "../../engine/ecs/World.hpp"

#include "../components/Collider.hpp"

#include "engine/core/Types.hpp"

class EntityFactory
{
public:
    EntityFactory(World& world): _world(world) {}    

    Entity createPlayer(TextureID texture, int x = 0, int y = 0, int size = -1);
    Entity createPlatform(
        TextureID texture,
        int x,
        int y,
        int width,
        int height,
        ColliderType type = ColliderType::Solid
    );
private:
    World& _world;
};
