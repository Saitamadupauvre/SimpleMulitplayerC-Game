#pragma once

#include "./Clock.hpp"
#include "../render/Renderer.hpp"

#include "../input/InputManager.hpp"

#include "engine/scene/IScene.hpp"

#include <memory>

constexpr int SUCCESS_STATUS = 0;
constexpr int FAILURE_STATUS = 1;

class Application
{
public:
    Application();

    void run();

    int getExitCode() const { return _exitStatus; }

private:
    void processEvents();

private:
    bool _running = true;
    std::unique_ptr<IScene> _scene;
    Clock _clock;
    InputManager _input;
    Renderer _renderer;

    double _accumulator = 0.0;

    int _exitStatus = SUCCESS_STATUS;
};
