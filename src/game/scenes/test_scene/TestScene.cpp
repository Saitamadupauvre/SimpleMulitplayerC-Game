#include "./TestScene.hpp"

#include "../../components/PlayerController.hpp"
#include "../../components/Velocity.hpp"
#include "../../systems/gameplay/PhysicsSystem.hpp"
#include "../../systems/rendering/RenderSystem.hpp"

#include "game/config/GameConfig.hpp"

TestScene::TestScene(TextureID playerTexture)
    : _entityFactory(_world), _playerTexture(playerTexture)
{
    _world.registerSystem<PhysicsSystem>();
    _world.registerSystem<RenderSystem>();
    spawnDuelPlayers();
}

void TestScene::spawnDuelPlayers()
{
    _playerEntities.push_back(
        _entityFactory.createPlayer(_playerTexture, GameConfig::Duel::LeftSpawnX, GameConfig::Duel::SpawnY)
    );
}

void TestScene::applyPlayerInput(const IInput& inputManager)
{
    for (const Entity entity : _playerEntities) {
        auto& velocity = _world.getComponent<Velocity>(entity);
        auto& controller = _world.getComponent<PlayerController>(entity);

        float horizontal = 0.0f;
        if (inputManager.isActionPressed(InputAction::MoveLeft)) {
            horizontal -= 1.0f;
        }
        if (inputManager.isActionPressed(InputAction::MoveRight)) {
            horizontal += 1.0f;
        }

        velocity.vx = horizontal * controller.moveSpeed;

        if (inputManager.isActionJustPressed(InputAction::MoveUp) && controller.onGround) {
            velocity.vy = -controller.jumpSpeed;
            controller.onGround = false;
        }
    }
}

void TestScene::onEvent(const SDL_Event& event)
{
    (void)event;
}

void TestScene::onUpdate(const IInput& inputManager, double dt)
{
    applyPlayerInput(inputManager);
    _world.updateSystems(static_cast<float>(dt));
}

void TestScene::onRender(IRenderer& renderer, double alpha)
{
    _world.renderSystems(renderer, alpha);
}
