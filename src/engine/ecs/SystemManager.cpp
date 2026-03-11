#include "SystemManager.hpp"

void SystemManager::entityDestroyed(Entity e)
{
    for (const std::type_index& type : _systemOrder) {
        _systems.at(type)->removeEntity(e);
    }
}

void SystemManager::entitySignatureChanged(Entity e, const Signature& entitySignature)
{
    for (const std::type_index& type : _systemOrder) {
        auto& system = _systems.at(type);
        const Signature& systemSig = _signatures.at(type);

        if ((entitySignature & systemSig) == systemSig) {
            system->addEntity(e);
        } else {
            system->removeEntity(e);
        }
    }
}

void SystemManager::updateAll(World& world, float dt)
{
    for (const std::type_index& type : _systemOrder) {
        _systems.at(type)->update(world, dt);
    }
}

void SystemManager::renderAll(World& world, IRenderer& renderer, double alpha)
{
    for (const std::type_index& type : _systemOrder) {
        _systems.at(type)->render(world, renderer, alpha);
    }
}
