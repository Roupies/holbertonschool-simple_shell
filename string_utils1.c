#include "shell.h"
#include <stddef.h> /* Added to define size_t */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _strcpy - Copy a string from src to dest
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: The destination buffer (dest)
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if the strings are equal,
 * a positive value if s1 > s2,
 * a negative value if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strncmp - Compare up to n characters of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 *
 * Return: 0 if the first n characters are equal,
 * a positive value if s1 > s2,
 * a negative value if s1 < s2
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (i < n && s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		i++;
	}

	if (i == n)
		return (0); /* Strings are equal up to n characters */

	return (s1[i] - s2[i]);
}
