#ifndef SHELL
#define SHELL

#define MAX 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

extern char **environ;
void execute(char *command, char *prog_name);
char *read_line(void);
void fork_execute(char *command, char *prog_name);

#endif
