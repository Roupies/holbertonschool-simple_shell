#include "shell.h"

extern char **environ;

/**
 * _get_path - Retrieves the PATH environment variable
 *
 * Return: Pointer to the PATH string or NULL if not found
 */
char *_get_path(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * find_in_path - Searches for a command in the PATH directories
 * @command: Name of the command
 *
 * Return: Full path to command (must be freed), or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	size_t len;

	if (_strchr(command, '/'))
		return (_strdup(command));

	path = _get_path();
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
	{
		perror("Error duplicating path");
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = _strlen(dir) + _strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			perror("Error allocating memory for full_path");
			free(path_copy);
			return (NULL);
		}

		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) ==0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

void execute_command(char **args, char *prog_name)
{
	pid_t pid;
	char *cmd_path;

	if (args[0] == NULL)
	{
		fprintf(stderr, "%s: command not found\n", prog_name);
		return;
	}

	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			free(cmd_path);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd_path);
	}
}
