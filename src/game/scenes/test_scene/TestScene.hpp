#pragma once

#include "engine/scene/IScene.hpp"
#include <SDL2/SDL.h>

#include <vector>

#include "../../../engine/ecs/World.hpp"
#include "../../entities/EntityFactory.hpp"

class TestScene : public IScene
{
public:
    explicit TestScene(TextureID playerTexture);

    void onEvent(const SDL_Event& event) override;
    void onUpdate(const IInput& inputManager, double dt) override;
    void onRender(IRenderer& renderer, double alpha) override;

private:
    void applyPlayerInput(const IInput& inputManager);
    void spawnPlatforms();
    void spawnDuelPlayers();

private:
    World _world;
    EntityFactory _entityFactory;
    TextureID _playerTexture = 0;
    std::vector<Entity> _playerEntities;
};
