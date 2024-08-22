#include "shell.h"

/**
 * main- Driver
 * @ac: argument count
 * @av: argument vectori
 * Return: 0 on success
 */

int main(int ac __attribute__((unused)), char **av)
{
	char *command;

	while (1)/*infinite loop*/
	{
		command = read_line();
		if (command == NULL)/*EOF (Ctrl+D)*/
		{
			break;
		}
		if (strlen(command) == 0)/*if command line is empty*/
		{
			free(command);
			continue;
		}
		exec_commands(command, av[0]);/* multiple commands */
		free(command);
	}
	if (isatty(STDIN_FILENO))
	{
		printf("\n");
	}
	return (0);
}


/**
 * print_env- Prints environment variables
 */


void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * prepare_command - funcion
 * @args: args
 * @path: path
 */

void prepare_command(char *args[], char *path)
{
	if (strchr(args[0], '/') == NULL)
	{
		sprintf(path, "/bin/%s", args[0]);
		args[0] = path;
	}
}
