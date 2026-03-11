#include "EntityFactory.hpp"

#include "../components/Collider.hpp"
#include "../components/PlayerController.hpp"
#include "../components/Transform.hpp"
#include "../components/Sprite.hpp"
#include "../components/Velocity.hpp"

#include "game/config/GameConfig.hpp"

Entity EntityFactory::createPlayer(TextureID texture, int x, int y, int size)
{
    Entity player = _world.createEntity();

    Transform transform;
    transform.position = Vec2{static_cast<float>(x), static_cast<float>(y)};

    Sprite sprite;
    sprite.texture = texture;
    sprite.width = size > 0 ? size : GameConfig::Player::SpriteSize;
    sprite.height = size > 0 ? size : GameConfig::Player::SpriteSize;

    Collider collider;
    collider.width = static_cast<float>(sprite.width);
    collider.height = static_cast<float>(sprite.height);

    PlayerController controller;

    _world.addComponent(player, transform);
    _world.addComponent(player, sprite);
    _world.addComponent(player, collider);
    _world.addComponent(player, Velocity{});
    _world.addComponent(player, controller);
    return player;
}

Entity EntityFactory::createPlatform(
    TextureID texture,
    int x,
    int y,
    int width,
    int height,
    ColliderType type
)
{
    Entity platform = _world.createEntity();

    Transform transform;
    transform.position = Vec2{static_cast<float>(x), static_cast<float>(y)};

    Sprite sprite;
    sprite.texture = texture;
    sprite.width = width;
    sprite.height = height;

    Collider collider;
    collider.width = static_cast<float>(width);
    collider.height = static_cast<float>(height);
    collider.type = type;

    _world.addComponent(platform, transform);
    _world.addComponent(platform, sprite);
    _world.addComponent(platform, collider);
    return platform;
}
