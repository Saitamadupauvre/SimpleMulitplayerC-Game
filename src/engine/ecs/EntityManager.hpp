#pragma once

#include <queue>

#include "./Entity.hpp"

class EntityManager
{
public:
    Entity create();
    void destroy(Entity entity);

private:
    Entity _next = 0;
    std::queue<Entity> _free;
};