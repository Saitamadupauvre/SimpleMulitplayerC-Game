add_library(engine_lib
    core/SceneManager.cpp
    core/Clock.cpp
    core/Application.cpp

    input/InputManager.cpp

    ecs/EntityManager.cpp
)

target_include_directories(engine_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
