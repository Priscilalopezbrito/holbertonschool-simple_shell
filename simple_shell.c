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
 * find_in_path- path
 * @filename: filename
 * Return: char *
 */
char *find_in_path(char *filename)
{
	char *token;
	char full_path[1024];
	char *path = getenv("PATH");
	char *path_copy = strdup(path);

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found.\n");
		return (NULL);
	}
	if (path_copy == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return (NULL);
	}
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, filename);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
