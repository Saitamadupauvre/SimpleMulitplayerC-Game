#include "EntityFactory.hpp"

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

    PlayerController controller;
    controller.groundY = transform.position.y;

    _world.addComponent(player, transform);
    _world.addComponent(player, sprite);
    _world.addComponent(player, Velocity{});
    _world.addComponent(player, controller);
    return player;
}
