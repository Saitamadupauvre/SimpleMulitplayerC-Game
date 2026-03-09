add_library(game_lib
    scenes/factory/SceneFactory.cpp
    scenes/test_scene/TestScene.cpp

    entities/factory/EntityFactory.cpp

    systems/render/RenderSystem.cpp
)

target_include_directories(game_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(game_lib PUBLIC
    engine_lib
)
