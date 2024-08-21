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
	if (execve(command, av, environ) == -1)/*13-16 add issaty to handle*/
	{
		if (isatty(STDIN_FILENO))
		{
			fprintf(stderr, "%s: %s: ", prog_name, command);
			perror("");
		}
		else
		{
			perror(prog_name);
		}
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
	command[_strcspn(command, "\n")] = 0;
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
	if (pid == -1)
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

/**
 * _strcspn- custom strcspn function
 * @s1: string
 * @s2: string
 * Return: ret
 */
size_t _strcspn(const char *s1, const char *s2)
{
	size_t ret = 0;

	while (*s1)
	{
		if (strchr(s2, *s1))
		{
			return (ret);
		}
		else
		{
			s1++, ret++;
		}
	}
	return (ret);
}
