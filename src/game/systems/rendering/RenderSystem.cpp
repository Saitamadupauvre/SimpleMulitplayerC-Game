#include "RenderSystem.hpp"
#include "../../components/Transform.hpp"
#include "../../components/Sprite.hpp"

void RenderSystem::render(World& world, IRenderer& renderer, double alpha)
{
    (void)alpha;

    for (const Entity& e: entities) {

        auto& transform = world.getComponent<Transform>(e);
        auto& sprite = world.getComponent<Sprite>(e);

        renderer.draw(
            sprite.texture,
            transform.position,
            transform.rotation,
            transform.scale,
            sprite.width,
            sprite.height
        );
    }
}

Signature RenderSystem::getSignature() const
{
    static const Signature sig = [] {
        Signature value;
        value.set(getComponentTypeID<Transform>());
        value.set(getComponentTypeID<Sprite>());
        return value;
    }();

    return sig;
}
