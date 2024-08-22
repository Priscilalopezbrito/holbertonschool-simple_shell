#include "shell.h"
/**
 * execute- execve
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
 * fork_execute- fork process
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
 * exec_commands- handles multiple commands
 * separated by spaces or newline
 * @command: command
 * @prog_name: name
 */

void exec_commands(char *command, char *prog_name)
{
	char *args[MAX];
	int i = 0;
	char *token;
	char *path;

	token = strtok(command, " ");
	while (token != NULL && i < MAX - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	if (args[0] != NULL)
	{
		if (args[0][0] == '/' || args[0][0] == '.')
		{
			path = args[0];
		}
		else
		{
			path = find_in_path(args[0]);
		}
		if (path != NULL && access(path, X_OK) == 0)
		{
			args[0] = path;
			fork_execute(args, prog_name);
			if (path != args[0])
			{
				free(path); /* Free if path_cmd was allocated by find_in_path */
			}
		}
		else
		{
			fprintf(stderr, "%s: Command not found\n", args[0]);
			if (path != args[0] && path != NULL)
			{
				free(path); /* Free if path_cmd was allocated but not used */
			}
		}
	}
}


