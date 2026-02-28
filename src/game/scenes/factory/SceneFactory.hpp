#pragma once

#include <stdexcept>
#include <string>
#include <memory>

#include "engine/IScene.hpp"

enum class SceneType {
    Test,
};

class SceneFactory
{
public:

    static std::unique_ptr<IScene> createScene(SceneType type);

public:
    class SceneFactoryException : public std::exception
    {
    public:
        SceneFactoryException(const std::string& msg): _msg(msg) {}
        const char* what() const noexcept override { return _msg.c_str(); }
    private:
        std::string _msg;
    };
};
