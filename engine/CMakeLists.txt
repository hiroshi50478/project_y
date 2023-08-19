add_library(engine SHARED)
    
target_compile_options(engine PRIVATE ${COMPILE_OPTIONS})
target_compile_features(engine PRIVATE ${COMPILE_FEATURES})

target_sources(engine PRIVATE
    #${CMAKE_SOURCE_DIR}/external/glew-2.2.0/src/glew.c
    src/render.c
)

target_include_directories(engine PUBLIC
    include
    ${GLFW_include_path}
    ${GLEW_include_path}
)

target_link_libraries(engine PUBLIC
    ${GLFW_lib_path}
    ${GLEW_lib_path}
    opengl32
)

add_custom_command(
    TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/engine/libengine.dll
    ${CMAKE_SOURCE_DIR}/libengine.dll
)
message("   libengine.dll will be copied at the end of building")