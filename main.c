#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

char* get_input () {
    char* input = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(input, BUFFER_SIZE, stdin);

    return input;
}

void shell_loop(void) {
    char* input;
    char** args;
    int status = 1;

    do {
        printf("> ");
        input = get_input();

        free(input);
    } while (status);
}

int main (int argc, char** argv) {
    shell_loop();

    return EXIT_SUCCESS;
}


