#include "shell.h"

/**
 * execute_command - Main function to execute a command
 * @args: Parsed command and arguments
 * @prog_name: Name of the shell program (for error messages)
 */
void execute_command(char **args, char *prog_name)
{
	char *cmd_path;

	cmd_path = find_in_path(args[0]);
	if (cmd_path == NULL)
	{
		handle_error(prog_name, args);
		return;
	}
	execute_in_fork(cmd_path, args, prog_name);
}

/**
 * execute_in_fork - Forks and executes a command in the child process
 * @cmd_path: Full path of the command to execute
 * @args: Command arguments
 * @prog_name: Program name (unused, kept for conformity)
 */
void execute_in_fork(char *cmd_path, char **args, char *prog_name)
{
	pid_t pid;

	(void)prog_name;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		exec_command(cmd_path, args);
	}
	else
	{
		wait_for_child(pid);
	}
}

/**
 * exec_command - Executes a command with execve
 * @cmd_path: Full path of the command
 * @args: Command arguments
 */
void exec_command(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		perror("Error executing command");
		exit(1);
	}
}

/**
 * wait_for_child - Waits for a child process and handles its exit status
 * @pid: PID of the child process
 */
void wait_for_child(pid_t pid)
{
	int status, exit_status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
		{
			printf("Child exited with status %d\n", exit_status);
		}
	}
}

/**
 * handle_error - Prints an error message when a command is not found
 * @prog_name: Name of the shell program
 * @args: Command and arguments
 */
void handle_error(char *prog_name, char **args)
{
	fprintf(stderr, "%s: command not found: %s\n", prog_name, args[0]);
}

