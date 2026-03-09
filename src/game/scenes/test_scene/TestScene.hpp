#pragma once

#include "engine/IScene.hpp"
#include <SDL2/SDL.h>

#include "../../../engine/ecs/World.hpp"
#include "../../../engine/ecs/SystemManager.hpp"
#include "../../entities/factory/EntityFactory.hpp"

class TestScene : public IScene
{
public:
    TestScene();

    void onEvent(const SDL_Event& event) override;
    void onUpdate(const IInput& inputManager, double dt) override;
    void onRender(IRenderer& renderer, double alpha) override;

private:
    World _world;
    EntityFactory _entityFactory;
    SystemManager _systemManager;
};
