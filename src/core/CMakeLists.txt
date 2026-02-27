add_library(core_lib
    SceneManager.cpp
    Clock.cpp
    Application.cpp
)

target_include_directories(core_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
