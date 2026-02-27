add_subdirectory(scenes)
add_subdirectory(core)

add_executable(multiplayer main.cpp)

set_target_properties(multiplayer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

target_link_libraries(multiplayer PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    core_lib
    scenes_lib
)
