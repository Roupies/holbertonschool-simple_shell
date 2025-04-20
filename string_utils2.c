#include "shell.h"
#include <stddef.h> /* Added to define size_t */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _strlen - Calculate the length of a string
 * @s: String
 *
 * Return: Length of the string
 */
size_t _strlen(const char *s)
{
	size_t len = 0;

	while (s[len] != '\0')
	{
		len++;
	}

	return (len);
}

/**
 * _strcat - Concatenate two strings
 * @dest: Destination string
 * @src: Source string
 *
 * Return: Pointer to the destination string (dest)
 */
char *_strcat(char *dest, const char *src)
{
	size_t i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i + j] = src[j];
	}
	dest[i + j] = '\0';

	return (dest);
}
/**
 * _strchr - Locate a character in a string
 * @s: String to search
 * @c: Character to find
 *
 * Return: Pointer to the first occurrence of c in s, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0') /* Handle null-terminator case */
		return ((char *)s);

	return (NULL);
}
/**
 * _strdup - Duplicate a string
 * @s: String to duplicate
 *
 * Return: Pointer to the newly allocated duplicate string, or NULL if failed
 */
char *_strdup(const char *s)
{
	size_t len = 0;
	size_t i;
	char *dup;

	if (!s)
		return (NULL);

	while (s[len])
		len++;

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = s[i];
	dup[len] = '\0';

	return (dup);
}
