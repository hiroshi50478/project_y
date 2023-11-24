#define DEBUG

#include <stdio.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_loader.h>
#include <obj_loader.h>


GLFWwindow* window;
GLuint VAO, VBO, EBO;
GLuint shaderProgram;
GLuint count;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


void Engine_init(int window_width, int window_height, char title[], bool full_screen) {
    #ifdef DEBUG
        if(!glfwInit()) {
            printf("!!! ERROR in glfwInit !!!\n");
        } else {
            printf("COMPLETE glfwInit\n");
        }
    #else
        glfwInit();
    #endif // DEBUG

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (full_screen) {
        window_width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
        window_height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
        window = glfwCreateWindow(window_width, window_height, title, glfwGetPrimaryMonitor(), NULL);
    } else {
        window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
    }

    #ifdef DEBUG
        if (!window) {
            printf("!!! ERROR in glfwCreateWindow !!!\n");
        } else {
            printf("COMPLETE glfwCreateWindow\n");
        }
    #endif // DEBUG
    
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    gladLoadGL();

    glViewport(0, 0, window_width, window_height);


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = shader_load("C:/Users/takayama/Desktop/project_y/engine/shaders/default.vert");
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, NULL);
    glCompileShader(vertexShader);
    
    #ifdef DEBUG
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("!!! ERROR in vertexShader !!!\n%s", infoLog);
        } else {
            printf("COMPLETE vertexShader\n");
        }
    #endif // DEBUG


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSource = shader_load("C:/Users/takayama/Desktop/project_y/engine/shaders/default.frag");
    glShaderSource(vertexShader, 1, (const GLchar**)&fragmentSource, NULL);
    glCompileShader(fragmentShader);

    #ifdef DEBUG
    	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    	if (!success) {
    	    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("!!! ERROR in fragmentShader !!!\n%s", infoLog);
    	} else {
            printf("COMPLETE fragmentShader\n");
        }
    #endif // DEBUG


    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    #ifdef DEBUG
    	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    	if (!success) {
    	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            printf("!!! ERROR in linking shaders !!!\n%s", infoLog);
    	} else {
            printf("COMPLETE linking shaders\n");
        }
    #endif // DEBUG
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void Engine_exit() {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}


bool Engine_event_status() {
    return !glfwWindowShouldClose(window);
}


void Engine_event_check() {
    glfwPollEvents();
}


void Engine_update() {
    glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
}