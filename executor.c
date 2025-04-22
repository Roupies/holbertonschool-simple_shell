#include "shell.h"

/**
 * execute_command - Executes a command with argument in a child process
 * @args: Arguments passed to the command
 * @prog_name: The name of the program (shell) for error messages
 */
int execute_command(char **args, char *prog_name)
{
	pid_t pid;
	char *cmd_path;
	int status;

	if (args[0] == NULL)
	{
		fprintf(stderr, "%s: command not found\n", prog_name);
		return(127);
	}

	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
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

	else if (pid == 0)
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
		waitpid(pid, &status, 0);
		free(cmd_path);

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
		else if (WIFSIGNALED(status))
		{
			int signal_num = WTERMSIG(status);
			return (128 + signal_num);
		}
	}
	return (0);
}
