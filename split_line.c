#include "simple_shell.h"

/**
 * split_line - Tokenizes the input line.
 * @line: The input line.
 *
 * Return: Array of tokens (NULL terminated).
 */
char **split_line(char *line)
{
	char **tokens = NULL;
	char *token;
	int bufsize = 0;
	int i = 0;

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (bufsize + 2));
		if (tokens == NULL)
		{
			perror("allocation");
			exit(EXIT_FAILURE);
		}
		tokens[i++] = token;
		bufsize++;
		token = strtok(NULL, " ");
	}
	if (tokens)
		tokens[i] = NULL;

	return (tokens);
}
