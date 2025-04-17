#include "simple_shell.h"

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	int status = 1;
	char *args[2];

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

		args[0] = line;
		args[1] = NULL;

		status = execute_command(args);

		free(line);
	}

	return (0);
}
