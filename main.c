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
	int builtin_result;

	(void)ac;

	while (1)
	{
		display_prompt();
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		args = parse_line(line);
		if (!args || !args[0])
		{
			free_args(args);
			continue;
		}

		builtin_result = handle_builtins(args);
		if (builtin_result == 1)
		{
			continue;
		}
		else if (builtin_result == -1)
			break; /* time to exit */

		execute_command(args, av[0], line_count);
		free_args(args);
	}

	free(line);
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
 * Return: 1 if a builtin was executed, -1 if exit, 0 otherwise
 */
int handle_builtins(char **args)
{
	int i;

	if (_strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		return (-1); /* signal to exit */
		exit(0);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		free_args(args);
		return (1);
	}

	return (0);
}
