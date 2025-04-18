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

		/* Check if the command is a builtin */
		builtin_result = handle_builtins(args);
		if (builtin_result == 1)
		{
			/* Builtin executed successfully, continue loop */
			continue;
		}
		else if (builtin_result == -1)
		{
			/* Exit command received, break loop */
			break;
		}

		/* If it's not a builtin, search for the command in PATH and execute */
		execute_command(args, av[0]);

		/* Free the allocated arguments array */
		free_args(args);
	}

	free(line);  /* Free the input line */
	return (0);
}

/**
 * display_prompt - Print shell prompt
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))  /* Only show the prompt if it's interactive */
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
		return (-1);  /* Return -1 to signal to exit the shell */
	}

	if (_strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
		free_args(args);
		return (1);  /* Return 1 to indicate that a builtin command was executed */
	}

	return (0);  /* Return 0 if no builtin command was executed */
}

