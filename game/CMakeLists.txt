add_executable(game)
    
target_compile_options(game PRIVATE ${COMPILE_OPTIONS})
target_compile_features(game PRIVATE ${COMPILE_FEATURES})

target_sources(game PRIVATE
    src/main.c
)

target_include_directories(game PRIVATE
    include
    engine
)

target_link_libraries(game PRIVATE
    engine
)

add_custom_command(
    TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/game/game.exe
    ${CMAKE_SOURCE_DIR}/game.exe
)
message("   game.exe will be copied at the end of building")