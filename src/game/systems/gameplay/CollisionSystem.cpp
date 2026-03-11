#include "CollisionSystem.hpp"

#include <algorithm>

#include "../../components/Collider.hpp"
#include "../../components/PlayerController.hpp"
#include "../../components/Transform.hpp"
#include "../../components/Velocity.hpp"

#include "game/config/GameConfig.hpp"

struct AABB {
    float left;
    float right;
    float top;
    float bottom;
};

AABB makeAABB(const Transform& transform, const Collider& collider)
{
    return {
        transform.position.x,
        transform.position.x + collider.width,
        transform.position.y,
        transform.position.y + collider.height,
    };
}

bool intersects(const AABB& a, const AABB& b)
{
    return a.right > b.left && a.left < b.right && a.bottom > b.top && a.top < b.bottom;
}

bool resolveOneWayPlatform(
    Transform& dynamicTransform,
    Velocity& dynamicVelocity,
    const Collider& dynamicCollider,
    const AABB& dynamicBox,
    const AABB& staticBox,
    float dt
)
{
    if (dynamicVelocity.vy < 0.0f) {
        return false;
    }

    const float previousBottom = dynamicBox.bottom - (dynamicVelocity.vy * dt);
    const bool crossedTop = previousBottom <= staticBox.top && dynamicBox.bottom >= staticBox.top;
    if (!crossedTop) {
        return false;
    }

    dynamicTransform.position.y = staticBox.top - dynamicCollider.height;
    dynamicVelocity.vy = 0.0f;
    return true;
}

bool resolveSolidCollision(
    Transform& dynamicTransform,
    Velocity& dynamicVelocity,
    const AABB& dynamicBox,
    const AABB& staticBox
)
{
    const float overlapLeft = dynamicBox.right - staticBox.left;
    const float overlapRight = staticBox.right - dynamicBox.left;
    const float overlapTop = dynamicBox.bottom - staticBox.top;
    const float overlapBottom = staticBox.bottom - dynamicBox.top;

    if (overlapLeft <= 0.0f || overlapRight <= 0.0f || overlapTop <= 0.0f || overlapBottom <= 0.0f) {
        return false;
    }

    const float penetrationX = std::min(overlapLeft, overlapRight);
    const float penetrationY = std::min(overlapTop, overlapBottom);
    const float dynamicCenterX = (dynamicBox.left + dynamicBox.right) * 0.5f;
    const float staticCenterX = (staticBox.left + staticBox.right) * 0.5f;
    const float dynamicCenterY = (dynamicBox.top + dynamicBox.bottom) * 0.5f;
    const float staticCenterY = (staticBox.top + staticBox.bottom) * 0.5f;

    if (penetrationX < penetrationY) {
        if (dynamicCenterX < staticCenterX) {
            dynamicTransform.position.x -= penetrationX;
        } else {
            dynamicTransform.position.x += penetrationX;
        }
        dynamicVelocity.vx = 0.0f;
        return false;
    }

    if (dynamicCenterY < staticCenterY) {
        dynamicTransform.position.y -= penetrationY;
        if (dynamicVelocity.vy > 0.0f) {
            dynamicVelocity.vy = 0.0f;
        }
        return true;
    }

    dynamicTransform.position.y += penetrationY;
    if (dynamicVelocity.vy < 0.0f) {
        dynamicVelocity.vy = 0.0f;
    }
    return false;
}

void CollisionSystem::update(World& world, float dt)
{
    for (const Entity& dynamicEntity : entities) {
        if (!world.hasComponent<PlayerController>(dynamicEntity) ||
            !world.hasComponent<Velocity>(dynamicEntity)) {
            continue;
        }

        auto& transform = world.getComponent<Transform>(dynamicEntity);
        auto& velocity = world.getComponent<Velocity>(dynamicEntity);
        auto& collider = world.getComponent<Collider>(dynamicEntity);
        auto& controller = world.getComponent<PlayerController>(dynamicEntity);

        controller.onGround = false;
        bool touchedGround = false;

        for (const Entity& staticEntity : entities) {
            if (dynamicEntity == staticEntity || world.hasComponent<PlayerController>(staticEntity)) {
                continue;
            }

            const auto& staticTransform = world.getComponent<Transform>(staticEntity);
            const auto& staticCollider = world.getComponent<Collider>(staticEntity);
            const AABB dynamicBox = makeAABB(transform, collider);
            const AABB staticBox = makeAABB(staticTransform, staticCollider);

            if (!intersects(dynamicBox, staticBox)) {
                continue;
            }

            if (staticCollider.type == ColliderType::OneWayPlatform) {
                if (resolveOneWayPlatform(transform, velocity, collider, dynamicBox, staticBox, dt)) {
                    touchedGround = true;
                }
                continue;
            }

            if (resolveSolidCollision(transform, velocity, dynamicBox, staticBox)) {
                touchedGround = true;
            }
        }

        controller.onGround = touchedGround;
    }
}

Signature CollisionSystem::getSignature() const
{
    static const Signature sig = [] {
        Signature value;
        value.set(getComponentTypeID<Transform>());
        value.set(getComponentTypeID<Collider>());
        return value;
    }();

    return sig;
}
