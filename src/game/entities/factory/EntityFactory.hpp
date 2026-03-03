#pragma once

#include "../../../engine/ecs/World.hpp"

class EntityFactory
{
public:
    EntityFactory(World& world): _world(world) {}    

    Entity createPlayer(int x=0, int y=0);
private:
    World& _world;
};
