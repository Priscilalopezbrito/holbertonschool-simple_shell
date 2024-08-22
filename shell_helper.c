#include "shell.h"
/**
 * execute- executes a command using execve
 * @args: command
 * @prog_name: name
 **/
void execute(char **args, char *prog_name)
{
	if (execve(args[0], args, environ) == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			perror(prog_name);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
}


/**
 * read_line- reads user input
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
		if (isatty(STDIN_FILENO))
		{
			printf("\n");
		}
		free(command);
		exit(0);
	}
	command[_strcspn(command, "\n")] = 0;
	return (command);
}

/**
 * fork_execute- fork process to execute command
 * @args: command
 * @prog_name: program name
 **/
void fork_execute(char **args, char *prog_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return;
	}
	else if (pid == 0)/*child*/
	{
		execute(args, prog_name);
	}
	else /*parent*/
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * _strcspn- custom strcspn function
 * finds the first occurrence of
 * any character in s2 in the string s1
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

/**
 * exec_commands- Tokenizes a command string into
 * individual arguments using spaces or newlines as delimiters
 * @command: command
 * @prog_name: name
 */

void exec_commands(char *command, char *prog_name)
{
	char *token, *args[100];
	char *delim = "\n\t\r ";
	int argc = 0;
	char *path;

	path = malloc(700 * sizeof(char));
	if (path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = strtok(command, delim);
	while (token != NULL && argc < 99)
	{
		if (strlen(token) > 0)
		{
			args[argc++] = token;
		}
		token = strtok(NULL, delim);
	}
	args[argc] = NULL;/*end of array*/
	if (args[0] != NULL && strcmp(args[0], "exit") == 0)/**/
	{
		free(command);
		free(path);
		exit(0);
	}
	prepare_command(args, path);
	if (args[0] != NULL)
	{
		fork_execute(args, prog_name);
	}
	free(path);
}
