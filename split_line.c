#include "simple_shell.h"

/**
 * split_line - Tokenizes the input line.
 * @line: The input line.
 *
 * Return: Array of tokens (NULL terminated).
 */
char **split_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0;
	int token_count = 0;

	token = strtok(line, " ");
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, " ");
	}

	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, " ");
	}

	tokens[i] = NULL;

	return (tokens);
}
