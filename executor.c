#include "shell.h"

/**
 * execute_command - Executes a command with argument in a child process
 * @args: Arguments passed to the command
 * @prog_name: The name of the program (shell) for error messages
 *
 * Return: Exit status of the command,
 *         or 127 if command not found or failed to execute
 */
int execute_command(char **args, char *prog_name)
{
	pid_t pid;
	char *cmd_path;
	int status;
	int exit_status = 0;
	int signal_num = 0;

	/* Handle empty command */
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

	/* Fork to execute the command */
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
		/* Parent waits for the child to finish */
		waitpid(pid, &status, 0);
		free(cmd_path);

		/* Check if child exited successfully or was killed by a signal */
		if (status == 0)
		{
			/* Normal exit */
			exit_status = 0;
		}
		else if (status > 0)
		{
			/* Process terminated by a signal */
			signal_num = status;  /* signal_num is directly the status in case of signal termination */
			exit_status = 128 + signal_num;
		}
	}

	return (exit_status);
}

