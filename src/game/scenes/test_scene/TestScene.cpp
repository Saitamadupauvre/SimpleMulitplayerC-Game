#include "./TestScene.hpp"

#include "../../systems/render/RenderSystem.hpp"

TestScene::TestScene(): _entityFactory(_world)
{
    _systemManager.registerSystem<RenderSystem>();

    _entityFactory.createPlayer(800/2, 600/2);
}

void TestScene::onEvent(const SDL_Event& event)
{
}

void TestScene::onUpdate(const IInput& inputManager, double dt)
{
    
}

void TestScene::onRender(IRenderer& renderer, double alpha)
{
    _systemManager.renderAll(_world, renderer, alpha);
}
