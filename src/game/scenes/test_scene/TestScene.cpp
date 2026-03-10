#include "./TestScene.hpp"

#include "../../systems/rendering/RenderSystem.hpp"

#include "game/config/GameConfig.hpp"

TestScene::TestScene(TextureID playerTexture)
    : _entityFactory(_world), _playerTexture(playerTexture)
{
    _world.registerSystem<RenderSystem>();
    spawnDuelPlayers();
}

void TestScene::spawnDuelPlayers()
{
    _entityFactory.createPlayer(_playerTexture, GameConfig::Duel::RightSpawnX, GameConfig::Duel::SpawnY);
}

void TestScene::onEvent(const SDL_Event& event)
{
    (void)event;
}

void TestScene::onUpdate(const IInput& inputManager, double dt)
{
    (void)inputManager;
    _world.updateSystems(static_cast<float>(dt));
}

void TestScene::onRender(IRenderer& renderer, double alpha)
{
    _world.renderSystems(renderer, alpha);
}
