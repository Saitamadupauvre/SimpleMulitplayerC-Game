#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>

#include "System.hpp"

#include "engine/Signature.hpp"

class SystemManager
{
public:
    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args) {
        std::type_index type = typeid(T);

        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        _systems[type] = system;
        return system;
    }

    template<typename T>
    requires std::is_base_of_v<System, T>
    void SystemManager::setSignature(Signature signature) {
        std::type_index type = typeid(T);
        _signatures[type] = signature;
    }

    void entityDestroyed(Entity e);
    void entitySignatureChanged(Entity e, const Signature& entitySignature);

    void updateAll(class World& world, float dt);

private:
    std::unordered_map<std::type_index, Signature> _signatures;
    std::unordered_map<std::type_index, std::shared_ptr<System>> _systems;
};
