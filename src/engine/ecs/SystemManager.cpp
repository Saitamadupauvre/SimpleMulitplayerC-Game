#include "SystemManager.hpp"

void SystemManager::entityDestroyed(Entity e)
{
    for (auto& [_, system] : _systems) {
        system->entities.erase(e);
    }
}

void SystemManager::entitySignatureChanged(Entity e, const Signature& entitySignature)
{
    for (auto& [type, system] : _systems) {
        const Signature& systemSig = _signatures[type];

        if ((entitySignature & systemSig) == systemSig) {
            system->entities.insert(e);
        } else {
            system->entities.erase(e);
        }
    }
}

void SystemManager::updateAll(World& world, float dt)
{
    for (auto& [_, system] : _systems) {
        system->update(world, dt);
    }
}

void SystemManager::renderAll(World& world, IRenderer& renderer, double alpha)
{
    for (auto& [_, system] : _systems) {
        system->render(world, renderer, alpha);
    }
}
