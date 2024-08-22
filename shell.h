#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX 100


extern char **environ;
void execute(char **args, char *prog_name);
char *read_line(void);
void fork_execute(char **args, char *prog_name);
void exec_commands(char *command, char *prog_name);
void print_env(void);
char *find_command(char *command);
void prepare_command(char *args[], char *path);
int tokenize_command(char *command, char **args);

#endif
