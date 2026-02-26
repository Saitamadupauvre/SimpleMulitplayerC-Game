#pragma once

#include <memory>
#include "core/IScene.hpp"

#include "../scenes/factory/SceneFactory.hpp"

class SceneManager
{
public:
    SceneManager();
    void set(std::unique_ptr<IScene> scene) { _current = std::move(scene); }
    IScene& current() { return *_current; }

private:
    std::unique_ptr<IScene> _current;
};
