#include "./EntityManager.hpp"

Entity EntityManager::create()
{
    Entity entity;

    if (!_free.empty()) {
        entity = _free.front();
        _free.pop();
    } else {
        entity = _next++;
    }
    return entity;
}

void EntityManager::destroy(Entity entity)
{
    _free.push(entity);
}
