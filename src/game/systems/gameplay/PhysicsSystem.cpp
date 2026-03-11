#include "PhysicsSystem.hpp"

#include "../../components/PlayerController.hpp"
#include "../../components/Transform.hpp"
#include "../../components/Velocity.hpp"

void PhysicsSystem::update(World& world, float dt)
{
    for (const Entity& e : entities) {
        auto& transform = world.getComponent<Transform>(e);
        auto& velocity = world.getComponent<Velocity>(e);
        auto& controller = world.getComponent<PlayerController>(e);

        velocity.vy += controller.gravity * dt;

        transform.position.x += velocity.vx * dt;
        transform.position.y += velocity.vy * dt;
    }
}

Signature PhysicsSystem::getSignature() const
{
    static const Signature sig = [] {
        Signature value;
        value.set(getComponentTypeID<Transform>());
        value.set(getComponentTypeID<Velocity>());
        value.set(getComponentTypeID<PlayerController>());
        return value;
    }();

    return sig;
}
