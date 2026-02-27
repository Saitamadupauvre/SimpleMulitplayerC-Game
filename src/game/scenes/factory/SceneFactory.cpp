#include "./SceneFactory.hpp"

#include "../test_scene/TestScene.hpp"

std::unique_ptr<IScene> SceneFactory::createScene(SceneType type)
{
    switch (type) {
        case SceneType::Test: return std::make_unique<TestScene>();

        default: throw SceneFactoryException("Invalid scene type");
    }
}
