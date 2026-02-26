#include "./Application.hpp"

Application::Application()
{
    initSDL("Game", 800, 600);
}

Application::~Application()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
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
        _clock.tick();
        double frameTime = _clock.frameTime();

        _accumulator += frameTime;

        processEvents();

        while (_accumulator >= _clock.fixedDelta()) {
            _scenes.current().onUpdate(_clock.fixedDelta());
            _accumulator -= _clock.fixedDelta();
        }

        double alpha = _accumulator / _clock.fixedDelta();
        _scenes.current().onRender(*_renderer, alpha);
    }
}

void Application::initSDL(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        _exitStatus = FAILURE_STATUS;
        return;
    }

    _window = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width, height,
                               SDL_WINDOW_SHOWN);
    if (!_window){
        _exitStatus = FAILURE_STATUS;
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        _exitStatus = FAILURE_STATUS;
        return;
    }
}
