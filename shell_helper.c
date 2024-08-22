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
	command[strcspn(command, "\n")] = 0;
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
* tokenize_command- Tokenizes a command string into
* individual arguments using spaces or newlines as delimiters
* @command: command
* @args: array to store arguments
* Return: number of arguments
*/
int tokenize_command(char *command, char **args)
{
	char *token, *delim = "\n\t\r ";

	int argc = 0;

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
	return (argc);
}

/**
* exec_commands- executes a command
* @command: command
* @prog_name: name
*/
/**
* exec_commands- executes a command
* @command: command
* @prog_name: name
*/
void exec_commands(char *command, char *prog_name)
{
	char *args[100];
	char *path;

	path = malloc(700 * sizeof(char));
	if (path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tokenize_command(command, args);
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
