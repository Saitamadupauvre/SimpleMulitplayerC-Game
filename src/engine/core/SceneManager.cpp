#include "./SceneManager.hpp"

SceneManager::SceneManager()
{
    set(SceneFactory::createScene(SceneType::Test)); 
}
