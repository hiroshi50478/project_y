add_library(engine SHARED)
    
target_compile_options(engine PRIVATE ${COMPILE_OPTIONS})
target_compile_features(engine PRIVATE ${COMPILE_FEATURES})

target_sources(engine PRIVATE
    src/shader_loader.c
    src/obj_loader.c
    src/render.c
)

target_include_directories(engine PUBLIC
    external/include
    src
    include
)

target_link_directories(engine PUBLIC
    external/lib
)

target_link_libraries(engine PUBLIC
    libglad.a
    libglfw3.a
    opengl32
)

set_target_properties(engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)