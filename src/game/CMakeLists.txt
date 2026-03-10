add_library(game_lib
    scenes/test_scene/TestScene.cpp

    entities/EntityFactory.cpp

    systems/gameplay/PhysicsSystem.cpp
    systems/rendering/RenderSystem.cpp
)

target_include_directories(game_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(game_lib PUBLIC
    engine_lib
)
