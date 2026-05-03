#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "../include/input.h"
#include "../include/execute.h"
#include "../include/prompt.h"

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

int main() {
  shell_loop();

  return EXIT_SUCCESS;
}
