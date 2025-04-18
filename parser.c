#include "shell.h"

/**
 * parse_line - Splits a line into arguments
 * @line: Input string
 *
 * Return: Array of strings (arguments) or NULL on failure
 */
char **parse_line(char *line)
{
	char *token = NULL, **args = NULL, **tmp = NULL;
	int bufsize = 64, i = 0;

	args = malloc(sizeof(char *) * bufsize);
	if (!args)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		args[i] = _strdup(token);
		if (!args[i])
		{
			while (i--)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		if (i >= bufsize)
		{
			bufsize += 64;
			tmp = realloc(args, sizeof(char *) * bufsize);
			if (!tmp)
			{
				while (i--)
					free(args[i]);
				free(args);
				return (NULL);
			}
			args = tmp;
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

