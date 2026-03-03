#pragma once

#include "./EntityManager.hpp"
#include "ComponentArray.hpp"
#include "SystemManager.hpp"

#include "engine/Component.hpp"
#include "engine/Signature.hpp"

#include <memory>
#include <unordered_map>

class World
{
public:
    Entity createEntity();
    void destroyEntity(Entity e);

    template<typename T>
    requires std::is_base_of_v<Component, T>
    void addComponent(Entity e, T component) {
        const ComponentType type = getComponentTypeID<T>();
        if (!has(e)) return;

        getComponentArray<T>().insert(e, component);

        if (type >= MAX_COMPONENTS)
            throw std::logic_error("Too many component types, increase MAX BYTES amount");
        _entitySignatures[e].set(type);
        _systemManager.entitySignatureChanged(e, _entitySignatures[e]);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    void removeComponent(Entity e) {
        const ComponentType type = getComponentTypeID<T>();
        if (!has(e)) return;

        getComponentArray<T>().remove(e);

        if (type >= MAX_COMPONENTS)
            throw std::logic_error("Too many component types, increase MAX BYTES amount");
        _entitySignatures[e].reset(type);
        _systemManager.entitySignatureChanged(e, _entitySignatures[e]);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    T& getComponent(Entity e) {
        return getComponentArray<T>().get(e);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    bool hasComponent(Entity e) const {
        return getComponentArray<T>().has(e);
    }

    const Signature& getSignature(Entity e) const { return _entitySignatures.at(e); }

    template<typename T>
    std::shared_ptr<T> registerSystem() {
        return _systemManager.registerSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature sig) {
        _systemManager.setSignature<T>(sig);
    }

    void updateSystems(float dt) {
        _systemManager.updateAll(*this, dt);
    }

private:
    EntityManager _entityManager;
    SystemManager _systemManager;

    template<typename T>
    ComponentArray<T>& getComponentArray() {
        ComponentType typeID = getComponentTypeID<T>();

        if (typeID >= _componentArrays.size()) {
            _componentArrays.resize(typeID + 1);
        }
        if (!_componentArrays[typeID]) {
            _componentArrays[typeID] = std::make_unique<ComponentArray<T>>();
        }
        return *static_cast<ComponentArray<T>*>(_componentArrays[typeID].get());
    }

    std::vector<std::unique_ptr<IComponentArray>> _componentArrays;
    std::unordered_map<Entity, Signature> _entitySignatures;
};
