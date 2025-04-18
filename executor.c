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

    /* If the command contains '/', it's already a valid path */
    if (_strchr(command, '/'))
        return (_strdup(command));

    /* Get the PATH environment variable */
    path = _get_path();
    if (!path)
        return (NULL);

    /* Duplicate the PATH string to work with */
    path_copy = _strdup(path);
    if (!path_copy)
        return (NULL);

    /* Tokenize the PATH string to separate directories */
    dir = strtok(path_copy, ":");
    while (dir)
    {
        len = _strlen(dir) + _strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            free(path_copy);  // Free before returning NULL
            return (NULL);
        }

        /* Construct the full path to the command */
        _strcpy(full_path, dir);
        _strcat(full_path, "/");
        _strcat(full_path, command);

        /* Check if the command is executable */
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);  // Free before returning the full path
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);  // Free before returning NULL
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

    /* Find the full path of the command */
    cmd_path = find_in_path(args[0]);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: %d: %s: not found\n",
                prog_name, line_count, args[0]);
        return;
    }

    /* Create a new process using fork */
    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        free(cmd_path);
        return;
    }

    /* In the child process */
    if (pid == 0)
    {
        /* Execute the command */
        execve(cmd_path, args, environ);
        perror("execve");
        exit(127);
    }
    else
    {
        /* In the parent process */
        wait(NULL);
        free(cmd_path);
    }
}

