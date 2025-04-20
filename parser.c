#include "shell.h"

/**
 * parse_line - Splits a line into arguments
 * @line: Input string
 *
 * Return: Array of strings (arguments)
 */
char **parse_line(char *line)
{
	char *token = NULL, **args = NULL;
	int bufsize = 64, i = 0;

	args = malloc(sizeof(char *) * bufsize);
	if (!args)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		args[i++] = strdup(token);
		if (i >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, sizeof(char *) * bufsize);
			if (!args)
				return (NULL);
		}
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

/**
 * free_args - Frees an array of strings
 * @args: Arguments array
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
}
