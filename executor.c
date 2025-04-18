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

    // Si la commande contient déjà un '/' (chemin absolu ou relatif)
    if (_strchr(command, '/'))
        return (_strdup(command));  // Retourne la commande telle quelle

    // Recherche de la variable PATH
    path = _get_path();
    if (!path)
        return (NULL);  // Si PATH est absent

    // Dupliquer le PATH pour le manipuler sans altérer la variable
    path_copy = _strdup(path);
    if (!path_copy)
        return (NULL);  // En cas d'échec d'allocation

    // Parcourir les répertoires du PATH
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
            return (full_path);  // Commande trouvée, retourner le chemin complet
        }

        free(full_path);  // Libérer le chemin en cas d'échec
        dir = strtok(NULL, ":");  // Passer au répertoire suivant
    }

    free(path_copy);  // Libérer la copie du PATH
    return (NULL);  // La commande n'a pas été trouvée
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

    // Trouver le chemin complet de la commande
    cmd_path = find_in_path(args[0]);
    if (!cmd_path)
    {
        // Si la commande n'a pas été trouvée, afficher une erreur et retourner
        fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, args[0]);
        return;  // Retourner sans fork ni execve
    }

    // Créer un nouveau processus avec fork
    pid = fork();
    if (pid == -1)
    {
        // Si fork échoue, afficher une erreur et libérer la mémoire allouée
        perror("fork");
        free(cmd_path);
        return;
    }

    if (pid == 0)
    {
        // Processus enfant : exécuter la commande avec execve
        execve(cmd_path, args, environ);
        // Si execve échoue, afficher une erreur
        perror("execve");
        exit(127);  // Exit avec code d'erreur 127
    }
    else
    {
        // Processus parent : attendre que l'enfant termine
        wait(NULL);
        free(cmd_path);  // Libérer le chemin une fois l'exécution terminée
    }
}


