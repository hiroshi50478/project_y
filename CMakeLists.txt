cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)
project(project_y LANGUAGES C)


option(engine_building "" ON)
option(game_building "" ON)


set(COMPILE_OPTIONS
	-Wall
	-Wextra
	-Wpedantic
)
set(COMPILE_FEATURES 
	c_std_23
)

set(GLFW_include_path ${CMAKE_SOURCE_DIR}/external/glfw/include)
set(GLFW_lib_path ${CMAKE_SOURCE_DIR}/external/glfw/lib/libglfw3.a)

set(GLEW_include_path ${CMAKE_SOURCE_DIR}/external/glew/include)
set(GLEW_lib_path ${CMAKE_SOURCE_DIR}/external/glew/lib/libglew32.a)


if (engine_building)
    message("ENGINE building")
    add_subdirectory(engine)    
endif()


if (game_building)
    message("GAME building")
    add_subdirectory(game)
endif()
