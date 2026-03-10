#include "./Application.hpp"

#include "../../game/scenes/match/TestScene.hpp"

#include "game/config/GameConfig.hpp"

namespace {
constexpr int MAX_FIXED_UPDATES_PER_FRAME = 5;
}

Application::Application(): _renderer(GameConfig::Window::Width, GameConfig::Window::Height)
{
    const TextureID playerTexture = _renderer.loadTexture("assets/default_sprite.png");
    _scene = std::make_unique<TestScene>(playerTexture);
}

void Application::processEvents()
{
    _input.beginFrame();

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        _input.processEvent(event);
        _scene->onEvent(event);
    }

    if (_input.shouldQuit())
        _running = false;
}

void Application::run()
{
    if (_exitStatus != SUCCESS_STATUS) return;

    while (_running) {
        processEvents();

        _clock.tick();
        double frameTime = _clock.frameTime();

        _accumulator += frameTime;

        int updateSteps = 0;
        while (_accumulator >= _clock.fixedDelta() && updateSteps < MAX_FIXED_UPDATES_PER_FRAME) {
            _scene->onUpdate(_input, _clock.fixedDelta());
            _accumulator -= _clock.fixedDelta();
            ++updateSteps;
        }

        if (updateSteps == MAX_FIXED_UPDATES_PER_FRAME && _accumulator >= _clock.fixedDelta()) {
            // Drop excessive backlog to keep the simulation responsive under temporary spikes.
            _accumulator = _clock.fixedDelta();
        }

        double alpha = _accumulator / _clock.fixedDelta();
        _renderer.beginFrame();
        _scene->onRender(_renderer, alpha);
        _renderer.endFrame();
    }
}
