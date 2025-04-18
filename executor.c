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
			return (environ[i] + 5);  // Retourne la partie après "PATH="
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

	// Si la commande contient déjà un '/', on la traite comme un chemin absolu
	if (_strchr(command, '/'))
		return (_strdup(command));

	// Récupérer la variable PATH
	path = _get_path();
	if (!path)
		return (NULL);

	// Dupliquer la chaîne PATH pour la manipuler
	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	// Parcourir chaque répertoire dans le PATH
	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = _strlen(dir) + _strlen(command) + 2;  // Calculer la taille du chemin complet
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);  // Échec d'allocation
		}

		// Construire le chemin complet
		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		// Vérifier si le fichier est exécutable
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);  // Commande trouvée
		}

		free(full_path);  // Libérer le chemin en cas d'échec
		dir = strtok(NULL, ":");  // Passer au répertoire suivant
	}

	free(path_copy);  // Libérer la copie du PATH
	return (NULL);  // Commande non trouvée
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

	// Vérifier si la commande existe dans le PATH
	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		// Commande introuvable, afficher un message d'erreur
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, args[0]);
		return;
	}

	// Créer un nouveau processus avec fork
	pid = fork();
	if (pid == -1)
	{
		// En cas d'échec de fork
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		// Dans le processus enfant, exécuter la commande
		execve(cmd_path, args, environ);
		// Si execve échoue
		perror("execve");
		exit(127);  // Sortir avec un code d'erreur
	}
	else
	{
		// Dans le processus parent, attendre la fin de l'exécution
		wait(NULL);
		free(cmd_path);  // Libérer la mémoire allouée pour le chemin
	}
}

