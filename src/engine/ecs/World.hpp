#pragma once

#include "./EntityManager.hpp"
#include "ComponentArray.hpp"
#include "SystemManager.hpp"

#include "engine/core/Component.hpp"
#include "engine/render/IRenderer.hpp"
#include "engine/core/Signature.hpp"

#include <memory>
#include <stdexcept>
#include <unordered_map>

class World
{
public:
    Entity createEntity();
    void destroyEntity(Entity e);

    template<typename T>
    requires std::is_base_of_v<Component, T>
    void addComponent(Entity e, T component) {
        ensureEntityExists(e);

        const ComponentType type = getComponentTypeID<T>();
        if (type >= MAX_COMPONENTS)
            throw std::logic_error("Too many component types, increase MAX_COMPONENTS amount");

        getComponentArray<T>().insert(e, component);
        _entitySignatures[e].set(type);
        _systemManager.entitySignatureChanged(e, _entitySignatures[e]);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    void removeComponent(Entity e) {
        ensureEntityExists(e);

        const ComponentType type = getComponentTypeID<T>();
        if (type >= MAX_COMPONENTS)
            throw std::logic_error("Too many component types, increase MAX_COMPONENTS amount");

        getComponentArray<T>().remove(e);
        _entitySignatures[e].reset(type);
        _systemManager.entitySignatureChanged(e, _entitySignatures[e]);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    T& getComponent(Entity e) {
        ensureEntityExists(e);
        return getComponentArray<T>().get(e);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    const T& getComponent(Entity e) const {
        ensureEntityExists(e);

        const ComponentArray<T>* componentArray = getComponentArrayIfExists<T>();
        if (!componentArray) {
            throw std::logic_error("Component array does not exist for this type");
        }
        return componentArray->get(e);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    bool hasComponent(Entity e) const {
        if (!entityExists(e)) {
            return false;
        }

        const ComponentArray<T>* componentArray = getComponentArrayIfExists<T>();
        return componentArray && componentArray->has(e);
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

    void renderSystems(IRenderer& renderer, double alpha) {
        _systemManager.renderAll(*this, renderer, alpha);
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

    template<typename T>
    const ComponentArray<T>* getComponentArrayIfExists() const {
        ComponentType typeID = getComponentTypeID<T>();
        if (typeID >= _componentArrays.size() || !_componentArrays[typeID]) {
            return nullptr;
        }

        return static_cast<const ComponentArray<T>*>(_componentArrays[typeID].get());
    }

    bool entityExists(Entity e) const {
        return _entitySignatures.find(e) != _entitySignatures.end();
    }

    void ensureEntityExists(Entity e) const {
        if (!entityExists(e)) {
            throw std::logic_error("Entity does not exist in World");
        }
    }

    std::vector<std::unique_ptr<IComponentArray>> _componentArrays;
    std::unordered_map<Entity, Signature> _entitySignatures;
};
