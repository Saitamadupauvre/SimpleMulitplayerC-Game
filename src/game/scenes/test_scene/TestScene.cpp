#include "./TestScene.hpp"

#include "../../components/Collider.hpp"
#include "../../systems/gameplay/CollisionSystem.hpp"
#include "../../components/PlayerController.hpp"
#include "../../components/Velocity.hpp"
#include "../../systems/gameplay/PhysicsSystem.hpp"
#include "../../systems/rendering/RenderSystem.hpp"

#include "game/config/GameConfig.hpp"

TestScene::TestScene(TextureID playerTexture)
    : _entityFactory(_world), _playerTexture(playerTexture)
{
    _world.registerSystem<PhysicsSystem>();
    _world.registerSystem<CollisionSystem>();
    _world.registerSystem<RenderSystem>();
    spawnPlatforms();
    spawnDuelPlayers();
}

void TestScene::spawnPlatforms()
{
    _entityFactory.createPlatform(_playerTexture, 0, 560, 800, 40, ColliderType::Solid);
    _entityFactory.createPlatform(_playerTexture, 120, 460, 180, 24, ColliderType::OneWayPlatform);
    _entityFactory.createPlatform(_playerTexture, 380, 400, 220, 24, ColliderType::OneWayPlatform);
    _entityFactory.createPlatform(_playerTexture, 650, 320, 120, 24, ColliderType::Solid);
}

void TestScene::spawnDuelPlayers()
{
    _playerEntities.push_back(
        _entityFactory.createPlayer(_playerTexture, GameConfig::Duel::LeftSpawnX, 300)
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
