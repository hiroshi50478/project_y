#include <GL/glew.h>
#include <GLFW/glfw3.h>


extern GLuint EBO, VBO, VAO;


void Engine_init(int window_width, int window_height, char title[]);
void Engine_exit();
bool Engine_event_status();
void Engine_event_check();
void Engine_update();