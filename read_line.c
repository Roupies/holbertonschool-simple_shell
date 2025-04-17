#include "simple_shell.h"

/**
 * read_line - Reads a line from standard input.
 *
 * Return: Pointer to the line string, or NULL on EOF.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t len;

	len = getline(&line, &size, stdin);
	if (len == -1)
	{
		free(line);
		return (NULL);
	}

	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}

	return (line);
}
