#pragma once

#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <vector>

#include "System.hpp"

#include "engine/core/Signature.hpp"

class SystemManager
{
public:
    template<typename T, typename... Args>
    requires std::is_base_of_v<System, T>
    std::shared_ptr<T> registerSystem(Args&&... args) {
        std::type_index type = typeid(T);

        if (_systems.contains(type)) {
            throw std::logic_error("System already registered");
        }

        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        _systems[type] = system;
        _systemOrder.push_back(type);

        setSignature<T>(system->getSignature());
        return system;
    }

    template<typename T>
    requires std::is_base_of_v<System, T>
    void setSignature(Signature signature) {
        std::type_index type = typeid(T);
        _signatures[type] = signature;
    }

    void entityDestroyed(Entity e);
    void entitySignatureChanged(Entity e, const Signature& entitySignature);

    void updateAll(class World& world, float dt);
    void renderAll(class World& world, IRenderer& renderer, double alpha);

private:
    std::vector<std::type_index> _systemOrder;
    std::unordered_map<std::type_index, Signature> _signatures;
    std::unordered_map<std::type_index, std::shared_ptr<System>> _systems;
};
