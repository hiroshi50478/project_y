cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)
project(project_y LANGUAGES C)


option(engine_building "" ON)
option(game_building "" ON)


set(CMAKE_GENERATOR MinGW Makefiles)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_BUILD_TYPE DEBUG)
set(COMPILE_OPTIONS
	-Wall
	-Wextra
	-Wpedantic
)
set(COMPILE_FEATURES 
	c_std_23
)


if (engine_building)
    message("ENGINE building")
    add_subdirectory(engine)    
endif()


if (game_building)
    message("GAME building")
    add_subdirectory(game)
endif()
