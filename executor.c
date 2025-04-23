#include "shell.h"

/**
 * execute_command - Executes a command with arguments in a child process
 * @args: Arguments passed to the command
 * @prog_name: The name of the shell program (used for error messages)
 *
 * Return: Exit status of the command, or 127 if command not found or failed
 */
int execute_command(char **args, char *prog_name)
{
	pid_t pid;
	char *cmd_path;
	int status;
	int exit_status;
	int signal_num;

	if (args == NULL || args[0] == NULL)
		return (127);

	cmd_path = find_in_path(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %s: not found\n", prog_name, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (127);
	}

	if (pid == 0)
	{
		/* Child process executes the command */
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			free(cmd_path);
			exit(127);
		}
	}
	else
	{
		/* Parent process waits for child */
		waitpid(pid, &status, 0);
		free(cmd_path);

		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
		else if (WIFSIGNALED(status))
		{
			signal_num = WTERMSIG(status);
			return (128 + signal_num);
		}
	}

	return (0);
}

