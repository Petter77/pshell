#ifndef MYSHELL_INCLUDE_COMMAND_H_
#define MYSHELL_INCLUDE_COMMAND_H_

typedef struct {
  char** args;
  char* redirect_in;
  char* redirect_out;
  int append;
} command_t;

#endif  // MYSHELL_INCLUDE_COMMAND_H_
