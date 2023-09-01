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


void test2d_draw() {
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.25f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.25f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f 
    };
    GLuint indices[] = {
        0, 1, 5,
        1, 2, 3,
        5, 3, 4
    };

    gladLoadGL();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    count = 9;
}

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
    glShaderSource(vertexShader, 1, shader_load("C:/Users/takayama/Deskto/project_y/engine/shaders/default.vert"), NULL);
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
    glShaderSource(fragmentShader, 1, shader_load("C:/Users/takayama/Deskto/project_y/engine/shaders/default.frag"), NULL);
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