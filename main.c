#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

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

void print_indicator(int status) {
  char dir[1024];
  if (status == 0) {
    printf("%s >", getcwd(dir, 1024));
    fflush(stdout);
  }
  else {
    printf("%s "RED">" RESET, getcwd(dir, 1024));
    fflush(stdout);
  }
}

int shell_scripts(char** args, int* proc_status) {
  // exit
  if (strcmp(args[0], "exit") == 0) {
    exit(EXIT_SUCCESS);
  }
  // cd
  if (strcmp(args[0], "cd") == 0) {
    if (args[1] == NULL) {
      chdir(getenv("HOME"));
    } 
    else if (args[2] != NULL) {
      printf("cd: too many arguments\n");
      *proc_status = 1;
      return 1;
    } 
    else {
      if (chdir(args[1]) != 0) {
        perror("cd");
        *proc_status = 1;
        return 1;
      }
    }
    *proc_status = 0;
    return 1;
  }
  return 0;
}

void execute(char** args, int* proc_status) {
  int should_return = shell_scripts(args, proc_status);

  if (should_return) {
    return;
  }

  pid_t pid = fork();

  if (pid == 0) {
    execvp(args[0], args);
  } else {
    waitpid(pid, proc_status, 0);
  }
}

void shell_loop(void) {
  char *input;
  char **args;
  int should_run = 1;
  int proc_status = 0;

  do {
    print_indicator(proc_status);
    input = get_input();
    args = get_args(input);

    if (args[0] == NULL) continue;
    execute(args, &proc_status);
    free(input);
  } while (should_run);
}

int main (int argc, char** argv) {
  shell_loop();

  return EXIT_SUCCESS;
}
