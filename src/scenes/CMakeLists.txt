add_library(scenes_lib
    factory/SceneFactory.cpp
    
    test_scene/TestScene.cpp
)

target_include_directories(scenes_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
