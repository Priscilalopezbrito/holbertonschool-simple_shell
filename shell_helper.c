#include "shell.h"
/**
 * execute- execve
 * @command: command
 * @prog_name: name
 **/
void execute(char *command, char *prog_name)
{
	char *av[2];

	av[0] = command;
	av[1] = NULL;
	if (execve(command, av, environ) == -1)
	{
		perror(prog_name);
	}
}

/**
 * read_line- imput
 * Return: command
 **/
char *read_line(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t getinput;

	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
	getinput = getline(&command, &len, stdin);
	if (getinput == -1)
	{
		free(command);
		return (NULL);
	}
	command[strcspn(command, "\n")] = 0;
	return (command);
}

/**
 * fork_execute- fork process
 * @command: command
 * @prog_name: program name
 **/
void fork_execute(char *command, char *prog_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		free(command);
		return;
	}
	else if (pid == 0)/*child*/
	{
		execute(command, prog_name);
		free(command);
		exit(EXIT_FAILURE);
	}
	else /*parent*/
	{
		waitpid(pid, &status, 0);
	}
}
