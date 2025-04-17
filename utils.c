#include "shell.h"

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: Difference
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcpy - Copy a string
 * @dest: Destination buffer
 * @src: Source string
 */
void _strcpy(char *dest, const char *src)
{
	while ((*dest++ = *src++) != '\0')
		;
}

