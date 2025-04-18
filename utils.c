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
 * Return: 0 if the strings are equal, a positive value if s1 > s2, 
 *         a negative value if s1 < s2
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
 *         a positive value if s1 > s2, 
 *         a negative value if s1 < s2
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

	return (s1[i] - s2[i]); /* Return difference of the first unmatched characters */
}

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

