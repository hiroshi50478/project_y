#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_loader.h>
#include <obj_loader.h>


void Engine_init(int window_width, int window_height, char title[], bool full_screen);
void Engine_exit();
bool Engine_event_status();
void Engine_event_check();
void Engine_update();

void test2d_draw();