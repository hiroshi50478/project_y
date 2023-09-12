#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char * const* shader_load(char title[]) {
	FILE* file = fopen(title, "r");
 	int length = 0;

 	#ifdef DEBUG
	    if (!file) {
	        printf("!!! ERROR in loading shader %s !!!\n", title);
	    } else {
	    	printf("COMPLETE loading shader %s\n", title);
	    }
	#endif // DEBUG
 
	while (fgetc(file) != EOF) {
		++length;
	}

	rewind(file);

    char shader_source[length];

	for (int i = 0; i < length; ++i) {
		shader_source[i] = fgetc(file);
	}

    fclose(file);

	const char* a;
	strcpy(a, shader_source);
	const char* const* b = a;

    return b;
} 