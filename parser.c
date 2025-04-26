#include "shell.h"

/**
 * parse_line - Splits a line into arguments
 * @line: Input string
 *
 * Return: Array of strings (arguments)
 */
char **parse_line(char *line)
{
	char *token = NULL, **args = NULL, **tmp = NULL;
	int i = 0, j;

	token = strtok(line, " \t\n");
	while (token)
	{
		tmp = malloc(sizeof(char *) * (i + 2));
		if (!tmp)
		{
			for (j = 0; j < i; j++)
				free(args[j]);
			free(args);
			return (NULL);
		}
		for (j = 0; j < i; j++)
			tmp[j] = args[j];
		tmp[i] = _strdup(token);
		if (!tmp[i])
		{
			for (j = 0; j < i; j++)
				free(tmp[j]);
			free(tmp);
			free(args);
			return (NULL);
		}
		tmp[i + 1] = NULL;

		free(args);
		args = tmp;
		i++;

		token = strtok(NULL, " \t\n");
	}
	return (args);
}

/**
 * free_args - Frees an array of strings
 * @args: Arguments array
 *
 * Return: Nothing
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
