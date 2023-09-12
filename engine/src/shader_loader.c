#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


GLchar* shader_load(char title[]) {
    FILE *file = fopen(title, "r");
    
	#ifdef DEBUG
	    if (!file) {
	        printf("!!! ERROR in loading shader %s !!!\n", title);
	    } else {
	    	printf("COMPLETE loading shader %s\n", title);
	    }
	#endif // DEBUG

    fseek(file, 0L, SEEK_END);
    long int length = ftell(file);
    rewind(file);

    GLchar* shader = memset(malloc(sizeof(GLchar) * (length + 1)), '\0', sizeof(GLchar) * (length + 1));
    fread(shader, sizeof(GLchar), length, file);
    fclose(file);

    return shader;
}