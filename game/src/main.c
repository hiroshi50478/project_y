#include <engine.h>


#define window_width 16 * 70
#define window_height 9 * 70


extern GLuint VAO, VBO, EBO;


int main() {
    Engine_init(window_width, window_height, "test", false);

    // test2d_draw();

    obj_load("C:/Users/takayama/Desktop/project_y/game/models/obj/cube.obj");

    while (Engine_event_status()) {
        Engine_event_check();
        Engine_update();
    }

    Engine_exit();

    return 0;
}