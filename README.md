# myshell

A Unix shell written from scratch in C. Built without tutorials — by reading man pages, experimenting, and understanding how processes actually work under the hood.

## Features

- Command execution via `fork` / `execvp`
- Built-in commands: `cd`, `exit`
- Colored prompt showing current working directory
- Red `>` indicator on non-zero exit status

## Building

```bash
make        # build
make re     # clean rebuild
make clean  # remove object files
make fclean # remove everything including build/
```

Binary is output to `build/main`.

## Usage

```bash
./build/main
```

```
/home//projects > ls -la
/home/projects > cd myshell
/home/projects/myshell > exit
```

## Project Structure

```
myshell/
├── include/
│   ├── execute.h
│   ├── input.h
│   └── prompt.h
├── src/
│   ├── main.c       # shell loop
│   ├── execute.c    # command execution, built-ins
│   ├── input.c      # input reading, argument parsing
│   └── prompt.c     # prompt display with ANSI colors
├── Makefile
└── README.md
```

## Implementation Notes

**Argument parsing** — custom tokenizer using two-pointer technique (`start`/`end`) with dynamic reallocation. No `strtok`.

**Process execution** — `fork` + `execvp` with `waitpid`. Parent always waits for child to finish before displaying next prompt.

**Built-in commands** — handled before `fork` since they need to modify shell state directly (e.g. `chdir` must run in the parent process, not a child).

**Prompt** — uses `getcwd` and ANSI escape codes. Exit status of the last command determines prompt color.

## Planned

- Redirections (`>`, `>>`, `<`)
- Pipes (`|`)
- Signal handling (`Ctrl+C`, `Ctrl+Z`)
- Job control (`&`, `fg`, `bg`)
