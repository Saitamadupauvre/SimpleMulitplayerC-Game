#pragma once

#include "./EntityManager.hpp"

#include "engine/Component.hpp"

#include <memory>
#include <unordered_map>

class World
{
public:
    Entity createEntity() { return _entityManager.create(); }
    void destroyEntity(Entity e) { _entityManager.destroy(e); }

    void addComponent(Entity e, std::shared_ptr<Component> comp)
    {
        _components[e].push_back(comp);
    }

    template<typename T>
    requires std::is_base_of_v<Component, T>
    T* getComponent(Entity e)
    {
        auto it = _components.find(e);
        if (it == _components.end()) return nullptr;

        for (auto& comp : it->second) {
            if (auto casted = dynamic_cast<T*>(comp.get()))
                return casted;
        }
        return nullptr;
    }

private:
    EntityManager _entityManager;
    std::unordered_map<Entity, std::vector<std::shared_ptr<Component>>> _components;
};
