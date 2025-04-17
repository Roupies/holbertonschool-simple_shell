#include "simple_shell.h"

/**
 * execute_command - Executes a command with fork and execve.
 * @args: Array of arguments (only the command in this project).
 *
 * Return: 1 to continue, 0 to exit.
 */
extern char **environ;

int execute_command(char **args)
{
        pid_t pid;
        int status;

        if (args[0] == NULL)
                return (1);

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (1);
}
