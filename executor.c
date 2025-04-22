#include "shell.h"

/**
 * execute_command - Main function to execute a command.
 * @args: Arguments passed to the command.
 * @prog_name: The name of the shell for error messages.
 *
 * Return: The exit status of the command executed.
 */
int execute_command(char **args, char *prog_name)
{
	char *cmd_path;

	/* Check if no command is passed */
	if (args[0] == NULL)
	{
		return (command_not_found(prog_name, args[0]));	}

	/* Find the full path for the command */
	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		return (command_not_found(prog_name, args[0]));
	}
	return (execute_in_fork(cmd_path, args));
}

/**
 * command_not_found - Handles the "command not found" error.
 * @prog_name: The name of the shell for error messages.
 * @command: The command that was not found.
 *
 * Return: Exit status for command not found.
 */
int command_not_found(char *prog_name, char *command)
{
	fprintf(stderr, "%s: %s: not found\n", prog_name, command);
	return (127);
}

/**
 * execute_in_fork - Forks a child process to execute the command.
 * @cmd_path: The full path to the command to execute.
 * @args: Arguments passed to the command.
 *
 * Return: Exit status of the command executed.
 */
int execute_in_fork(char *cmd_path, char **args)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (127);
	}
	else if (pid == 0)
	{
		return (execute_in_child(cmd_path, args));
	}
	else
	{
		return (wait_for_child(pid, status, cmd_path));
	}
}

/**
 * execute_in_child - Executes the command in the child process.
 * @cmd_path: The full path to the command to execute.
 * @args: Arguments passed to the command.
 *
 * Return: Exit status of the command executed.
 */
int execute_in_child(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		perror("execve");
		free(cmd_path);
		exit(127);
	}
	return (0); /* Should never be reached */
}

/**
 * wait_for_child - Waits for the child process to complete and returns status.
 * @pid: The PID of the child process.
 * @status: The status of the child process after waiting.
 * @cmd_path: The full path of the command to execute.
 *
 * Return: The exit status of the command executed.
 */
int wait_for_child(pid_t pid, int status, char *cmd_path)
{
	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status));
	}
	return (0);
}

