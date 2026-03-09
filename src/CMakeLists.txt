add_subdirectory(engine)
add_subdirectory(game)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(multiplayer main.cpp)

set_target_properties(multiplayer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

target_link_libraries(multiplayer PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    engine_lib
    game_lib
)
