#pragma once

#include "./SceneManager.hpp"
#include "./Clock.hpp"

#include "../input/InputManager.hpp"

#include <string>

constexpr int SUCCESS_STATUS = 0;
constexpr int FAILURE_STATUS = 1;

class Application
{
public:
    Application();
    ~Application();

    void run();

    int getExitCode() const { return _exitStatus; }

private:
    void processEvents();
    void update();
    void render();

    void initSDL(const char* title, int width, int height);

private:
    bool _running = true;
    SceneManager _scenes;
    Clock _clock;
    InputManager _input;

    double _accumulator = 0.0;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    int _exitStatus = SUCCESS_STATUS;

private:
    class ApplicationException : public std::exception
    {
    public:
        ApplicationException(const std::string& msg): _msg(msg) {}
        const char* what() const noexcept override { return _msg.c_str(); }
    private:
        std::string _msg;
    };
};
