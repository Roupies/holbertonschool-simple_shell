#include "shell.h"

int last_exit_status = 0;

/**
 * display_prompt - Print shell prompt
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * handle_input - Parse and execute a line of input
 * @line: The input line
 * @av: Argument vector for program name
 *
 * Return: -1 if "exit" builtin is called, 0 otherwise
 */
int handle_input(char *line, char **av)
{
	char **args;
	int builtin_result;


	args = parse_line(line);
	if (!args || !args[0])
	{
		free_args(args);
		return (0);
	}

	if (strcmp(args[0], "$?") == 0)
	{
		printf("%d\n", last_exit_status);
		free_args(args);
		return (0);
	}

	builtin_result = handle_builtins(args);
	if (builtin_result == -1)
	{
		free_args(args);
		return (-1);
	}

	last_exit_status = execute_command(args, av[0]);
	free_args(args);
	return (0);
}

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

	(void)ac;

	while (1)
	{
		display_prompt();
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		if (handle_input(line, av) == -1)
			break;
	}

	free(line);
	return (0);
}
