#include "shell.h"
#include <stddef.h> /* Pour définir size_t */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  /* Ajouté pour l'utilisation de access() */

/**
 * _get_path - Récupère la variable d'environnement PATH
 *
 * Return: Un pointeur vers la chaîne PATH, ou NULL si non trouvée
 */
char *_get_path(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		/* Cherche "PATH=" dans chaque élément de environ */
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5); /* Retourne la chaîne après "PATH=" */
	}
	return (NULL);
}

/**
 * find_in_path - Recherche une commande dans les répertoires définis dans PATH
 * @command: Le nom de la commande à rechercher
 *
 * Return: Le chemin absolu de la commande si trouvée (doit être libéré),
 *         ou NULL si la commande n'est pas trouvée
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *token, *full_path;
	size_t len;

	/* Si la commande contient déjà un '/' (chemin absolu), on la retourne telle quelle */
	if (_strchr(command, '/'))
		return (strdup(command));

	/* Récupère le PATH dans l'environnement */
	path = _get_path();
	if (!path)
		return (NULL);

	/* Crée une copie du PATH pour la découper */
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	/* Découpe le PATH par ":" pour itérer sur chaque répertoire */
	token = strtok(path_copy, ":");
	while (token)
	{
		/* Alloue de la mémoire pour construire le chemin complet */
		len = _strlen(token) + _strlen(command) + 2; /* +1 pour le '/' et +1 pour '\0' */
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL); /* Libère path_copy et retourne NULL en cas d'erreur */
		}

		/* Concatène le chemin du répertoire avec la commande */
		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		/* Vérifie si le fichier existe et est exécutable */
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free(path_copy); /* Libère path_copy dès que le chemin est trouvé */
			return (full_path); /* Retourne le chemin complet de la commande */
		}

		free(full_path); /* Libère full_path si la commande n'est pas trouvée dans ce répertoire */
		token = strtok(NULL, ":"); /* Passe au répertoire suivant */
	}
	free(path_copy); /* Libère la copie de PATH une fois qu'on a fini */
	return (NULL); /* Retourne NULL si la commande n'a pas été trouvée */
}

