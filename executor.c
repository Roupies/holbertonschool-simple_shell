#include "shell.h"

/**
 * execute_command - Executes a command with arguments in a child process
 * @args: Arguments passed to the command
 * @prog_name: The name of the shell program (used for error messages)
 *
 * Return: Exit status of the command
 *         127 if command not found or execve fails
 *         128 + signal number if terminated by a signal
 */
int execute_command(char **args, char *prog_name)
{
	pid_t pid;
	char *cmd_path;
	int status = 0;
	int exit_status = 0;

	/* Handle empty input or null command */
	if (!args || !args[0])
	{
		fprintf(stderr, "%s: command not found\n", prog_name);
		return (127);
	}

	/* Locate command in PATH */
	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %s: not found\n", prog_name, args[0]);
		return (127);
	}

	/* Fork to create child process */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (126);
	}

	if (pid == 0)
	{
		/* Child process: try to execute the command */
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			free(cmd_path);
			exit(127);
		}
	}
	else
	{
		/* Parent process: wait for the child */
		waitpid(pid, &status, 0);
		free(cmd_path);

		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			exit_status = 128 + WTERMSIG(status);
		}
	}

	return (exit_status);
}
