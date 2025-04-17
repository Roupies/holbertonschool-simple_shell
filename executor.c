#include "shell.h"

/**
 * find_in_path - Search for a command in the PATH
 * @command: Command name
 *
 * Return: Full path if found (must be freed), or NULL
 */
char *find_in_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy, *dir, *full_path;
	size_t len;

	if (!path)
		return (NULL);

	if (strchr(command, '/'))
		return (strdup(command)); /* already a path */

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
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


/**
 * execute_command - Execute a command using fork and execve
 * @args: Argument vector
 * @prog_name: Program name (from av[0])
 * @line_count: Line number (used for errors)
 */
void execute_command(char **args, char *prog_name, int line_count)
{
	pid_t pid;
	char *cmd_path;

	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, args[0]);
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
		execve(cmd_path, args, environ);
		perror("execve");
		exit(127);
	}
	else
	{
		wait(NULL);
		free(cmd_path);
	}
}

