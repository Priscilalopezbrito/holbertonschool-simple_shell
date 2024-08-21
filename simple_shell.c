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
		/*fork_execute(command, av[0]);*/
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
 * exec_commands- handles multiple commands
 * separated by spaces or newline
 * @command: command
 * @prog_name: name
 */
void exec_commands(char *command, char *prog_name)
{
	char *token;
	char *delim = "\n ";

	token = strtok(command, delim);
	while (token != NULL)
	{
		if (strlen(token) > 0)
		{
			fork_execute(token, prog_name);
		}
		token = strtok(NULL, delim);
	}
}
