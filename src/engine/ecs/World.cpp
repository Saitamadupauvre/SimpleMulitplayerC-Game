#include "World.hpp"

Entity World::createEntity()
{
    Entity e = _entityManager.create();

    _entitySignatures[e] = Signature{};
    return e;
}

void World::destroyEntity(Entity e)
{
    _entityManager.destroy(e);
    _entitySignatures.erase(e);
    _systemManager.entityDestroyed(e);

    for (std::unique_ptr<IComponentArray>& array : _componentArrays) {
        if (array) array->remove(e);
    }
}
