#include <unistd.h>
#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


void print_indicator(int status) {
  char dir[1024];
  if (status == 0) {
    printf("%s >", getcwd(dir, 1024));
    fflush(stdout);
  } else {
    printf("%s "RED">" RESET, getcwd(dir, 1024));
    fflush(stdout);
  }
}

