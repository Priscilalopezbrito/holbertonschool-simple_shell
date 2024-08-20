#include "shell.h"

/**
 * main- Driver
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 **/

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
		fork_execute(command, av[0]);
		free(command);
	}
	if (isatty(STDIN_FILENO))
	{
		printf("\n");
	}
	return (0);
}
