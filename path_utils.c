#include "shell.h"
#include <stddef.h> /* Added to define size_t */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _get_path - Retrieves the PATH environment variable
 *
 * Return: Pointer to the PATH string, or NULL if not found
 */
char *_get_path(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * create_full_path - Constructs the full path for a command
 * @path: The directory in the PATH variable
 * @command: The command to execute
 *
 * Return: A string containing the full path to the command
 */
char *create_full_path(char *path, char *command)
{
	char *full_path;

	full_path = malloc(strlen(path) + strlen(command) + 2);
	if (!full_path)
		return (NULL);
	sprintf(full_path, "%s/%s", path, command);
	return (full_path);
}

/**
 * find_in_path - Searches for a command in the PATH directories
 * @command: Name of the command
 *
 *Return:Full path to the command if found (must be freed),or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *token, *full_path;

	if (_strchr(command, '/'))
		return (strdup(command));

	path = _get_path();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("Erro duplicating path");
		return (NULL);
	}

	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = create_full_path(token, command);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}


		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
