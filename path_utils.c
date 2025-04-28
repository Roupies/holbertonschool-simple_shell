#include "shell.h"

/**
 * _get_path - Retrieves the PATH environment variable
 *
 * Return: A pointer to the PATH string, or NULL if not found
 */
char *_get_path(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		/* Look for "PATH=" in each element of environ */
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5); /* Return the string after "PATH=" */
	}
	return (NULL);
}

/**
 * find_in_path - Searches for a command in the directories listed in PATH
 * @command: The name of the command to search for
 *
 * Return: The absolute path of the command if found (must be freed),
 *         or NULL if the command is not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *token, *full_path;
	size_t len;

	/* If the command already contains a '/', return it as-is */
	if (_strchr(command, '/'))
		return (_strdup(command));

	/* Retrieve the PATH from the environment */
	path = _get_path();
	if (!path)
		return (NULL);

	/* Create a copy of PATH to split it */
	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	/* Split PATH by ":" to iterate over each directory */
	token = strtok(path_copy, ":");
	while (token)
	{
		/* Allocate memory to build the full path */
		len = _strlen(token) + _strlen(command) + 2; /* +1 for '/' and +1 for '\0' */
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL); /* Free path_copy and return NULL on error */
		}

		/* Concatenate the directory path with the command */
		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		/* Check if the file exists and is executable */
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free(path_copy); /* Free path_copy once the path is found */
			return (full_path); /* Return the full command path */
		}

		free(full_path); /* Free full_path if the command is not found in this directory */
		token = strtok(NULL, ":"); /* Move to the next directory */
	}
	free(path_copy); /* Free the copy of PATH once done */
	return (NULL); /* Return NULL if the command was not found */
}

