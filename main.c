#include "simple_shell.h"

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
void handle_sigint(int _sig)
{
	(void)_sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}


int main(void)
{
	char *line;
	int status = 1;
	char *args[2];

	signal(SIGINT, handle_sigint);

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

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		if (strchr(line, '\x1b'))
		{
			fprintf(stderr, "./shell: No such file or directory\n");
			free(line);
			continue;
		}

		args[0] = line;
		args[1] = NULL;

		status = execute_command(args);

		free(line);
	}

	return (0);
}
