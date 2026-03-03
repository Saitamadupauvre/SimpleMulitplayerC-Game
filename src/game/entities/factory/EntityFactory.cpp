#include "EntityFactory.hpp"

#include "../../components/Transform.hpp"
#include "../../components/Sprite.hpp"

Entity EntityFactory::createPlayer(int x, int y)
{
    Entity player = _world.createEntity();

    _world.addComponent(player, Transform{});
    _world.addComponent(player, Sprite{});
    return player;
}
