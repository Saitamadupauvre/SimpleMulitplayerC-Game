add_library(core_lib
    Application.cpp
    SceneManager.cpp
    Clock.cpp
)

target_include_directories(core_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
