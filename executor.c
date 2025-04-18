#include "shell.h"

extern char **environ;

/**
 * _get_path - Retrieves the PATH environment variable
 *
 * Return: Pointer to the PATH string or NULL if not found
 */
char *_get_path(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * find_in_path - Searches for a command in the PATH directories
 * @command: Name of the command
 *
 * Return: Full path to command (must be freed), or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	size_t len;

	/* Si la commande contient un '/', c'est déjà un chemin valide */
	if (_strchr(command, '/'))
	{
		/* Vérifie si le chemin est valide et exécutable */
		if (access(command, X_OK) == 0)
			return (_strdup(command));  // Commande valide
		else
			return (NULL);  // Commande invalide
	}

	/* Récupère la variable d'environnement PATH */
	path = _get_path();
	if (!path)
		return (NULL);

	/* Duplique la chaîne PATH pour la manipuler */
	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	/* Tokenize la chaîne PATH pour séparer les répertoires */
	dir = strtok(path_copy, ":");
	while (dir)
	{
		/* Ignore les répertoires vides */
		if (strlen(dir) == 0)
		{
			dir = strtok(NULL, ":");
			continue;
		}

		len = _strlen(dir) + _strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		/* Vérifie si le fichier est exécutable */
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Executes a command using fork and execve
 * @args: Argument vector
 * @prog_name: Program name (from av[0])
 * @line_count: Line number for error messages
 */
void execute_command(char **args, char *prog_name, int line_count)
{
	pid_t pid;
	char *cmd_path;

	/* Trouve le chemin complet de la commande */
	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_count, args[0]);
		return;
	}

	/* Crée un nouveau processus avec fork */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	/* Dans le processus enfant */
	if (pid == 0)
	{
		/* Exécute la commande */
		execve(cmd_path, args, environ);
		perror("execve");
		exit(127);
	}
	else
	{
		/* Dans le processus parent */
		wait(NULL);
		free(cmd_path);
	}
}

