#pragma once
#include <vector>
#include <unordered_map>
#include <cassert>

#include "engine/Component.hpp"
#include "exception/ComponentException.hpp"

#include "Entity.hpp"

using ComponentType = std::size_t;

inline ComponentType getUniqueComponentTypeID() {
    static ComponentType lastID = 0;
    return lastID++;
}

template<typename T>
inline ComponentType getComponentTypeID() noexcept {
    static ComponentType typeID = getUniqueComponentTypeID();
    return typeID;
}

struct IComponentArray {
    virtual ~IComponentArray() = default;

    virtual void remove(Entity entity) = 0;
    virtual bool has(Entity entity) = 0;
};

template<typename T>
requires std::is_base_of_v<Component, T>
class ComponentArray: public IComponentArray
{
public:
    void insert(Entity entity, T component) {
        if (!has(entity)) {
            return;
        }

        size_t newIndex = components.size();
        entityToIndex[entity] = newIndex;
        indexToEntity[newIndex] = entity;
        components.push_back(component);
    }

    void remove(Entity entity) override {
        if (!has(entity)) {
            return;
        }

        size_t index = entityToIndex[entity];
        size_t lastIndex = components.size() - 1;

        components[index] = components[lastIndex];
        Entity lastEntity = indexToEntity[lastIndex];
        entityToIndex[lastEntity] = index;
        indexToEntity[index] = lastEntity;

        components.pop_back();
        entityToIndex.erase(entity);
        indexToEntity.erase(lastIndex);
    }

    T& get(Entity entity) {
        if (!has(entity)) {
            throw ComponentException("Component doesn't exist when trying to get");
        }
        return components[entityToIndex[entity]];
    }

    bool has(Entity entity) override {
        return entityToIndex.find(entity) != entityToIndex.end();
    }

    std::vector<T>& getAll() { return components; }

private:
    std::vector<T> components;
    std::unordered_map<Entity, size_t> entityToIndex;
    std::unordered_map<size_t, Entity> indexToEntity;
};
