#include "shell.h"

/**
 * main - Entry point of the shell
 * @ac: Argument count (unused)
 * @av: Argument vector (used for program name)
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args = NULL;
	int line_count = 0;

	(void)ac;

	while (1)
	{
		display_prompt();
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			if (args)
				free_args(args);
			exit(0); /* Exit cleanly on Ctrl+D */
		}

		args = parse_line(line);
		if (!args || !args[0])
		{
			free_args(args);
			continue;
		}

		if (handle_builtins(args))
			continue;

		execute_command(args, av[0], line_count);
		free_args(args);
	}

	return (0);
}

/**
 * display_prompt - Print shell prompt
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
}

/**
 * handle_builtins - Check if a command is a builtin and run it
 * @args: Argument vector
 *
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtins(char **args)
{
	int i;

	/* Handle the 'exit' command */
	if (_strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		exit(0);
	}

	/* Handle the 'env' command */
	if (_strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
		free_args(args);
		return 1;  /* Command was handled */
	}

	return 0;  /* No builtin command handled */
}

