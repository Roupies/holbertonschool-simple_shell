#include "shell.h"

/**
 * execute_command - Executes a command with argument in a child process
 * @args: Arguments passed to the command
 * @prog_name: The name of the program (shell) for error messages
 */
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
