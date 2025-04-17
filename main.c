#include "simple_shell.h"

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = split_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	}

	return (0);
}
