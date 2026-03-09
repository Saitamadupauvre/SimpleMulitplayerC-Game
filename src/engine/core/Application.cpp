#include "./Application.hpp"

Application::Application(): _renderer(800, 600)
{
    _renderer.loadTexture("assets/default_sprite.png");
}

void Application::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            _running = false;

        _scenes.current().onEvent(event);
    }
}

void Application::run()
{
    if (_exitStatus != SUCCESS_STATUS) return;

    while (_running) {
        _input.update();
        if (_input.shouldQuit())
            _running = false;

        _clock.tick();
        double frameTime = _clock.frameTime();

        _accumulator += frameTime;

        processEvents();

        while (_accumulator >= _clock.fixedDelta()) {
            _scenes.current().onUpdate(_input, _clock.fixedDelta());
            _accumulator -= _clock.fixedDelta();
        }

        double alpha = _accumulator / _clock.fixedDelta();
        _renderer.beginFrame();
        _scenes.current().onRender(_renderer, alpha);
        _renderer.endFrame();
    }
}
