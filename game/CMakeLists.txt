add_executable(game)
    
target_compile_options(game PRIVATE ${COMPILE_OPTIONS})
target_compile_features(game PRIVATE ${COMPILE_FEATURES})

target_sources(game PRIVATE
    src/main.c
)

target_include_directories(game PRIVATE
    engine
)

target_link_libraries(game PRIVATE
    engine
)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)