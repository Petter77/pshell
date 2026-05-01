#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* get_input () {
    char* input = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(input, BUFFER_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0';

    return input;
}

char **get_args(char *input) {
    int cap = 2;
    int count = 0;
    char **args = malloc(sizeof(char *) * cap);

    char *start = input;

    while (*start != '\0') {
        while (*start == ' ') start++;
        if (*start == '\0') break;

        char *end = start;
        while (*end != ' ' && *end != '\0') end++;

        int len = end - start;
        char *token = malloc(len + 1);
        strncpy(token, start, len);
        token[len] = '\0';

        if (count + 1 >= cap) {
            cap *= 2;
            args = realloc(args, sizeof(char *) * cap);
        }
        args[count++] = token;

        start = end;
    }

    args[count] = NULL;
    return args;
}
void shell_loop(void) {
    char *input;
    char **args;
    int should_run = 1;
    int proc_status;

    do {
        printf("\n> ");
        fflush(stdout);
        input = get_input();
        args = get_args(input);

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
        } else {
            waitpid(pid, &proc_status, 0);
        }

        free(input);
    } while (should_run);
}
int main (int argc, char** argv) {
    shell_loop();
    

    return EXIT_SUCCESS;
}
