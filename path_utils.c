#include "shell.h"
#include <stddef.h> /* Added to define size_t */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

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
 * find_in_path - Searches for a command in the PATH directories
 * @command: Name of the command
 *
 *Return:Full path to the command if found (must be freed),or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *token, *full_path;
	size_t len;

	if (_strchr(command, '/'))
		return (strdup(command));

	path = _get_path();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		len = _strlen(token) + _strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);


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
