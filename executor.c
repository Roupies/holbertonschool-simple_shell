#include "shell.h"

/**
 * _get_path - Get the value of the PATH environment variable
 *
 * Return: Pointer to the PATH string, or NULL if not found
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
 * find_in_path - Search for a command in the PATH
 * @command: Command name
 *
 * Return: Full path if found (must be freed), or NULL if not found
 */
char *find_in_path(char *command)
{
    char *path = _get_path();
    char *path_copy, *dir, *full_path;
    size_t len;

    if (!path)
        return (NULL);

    if (_strchr(command, '/'))
        return (_strdup(command));

    path_copy = _strdup(path);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
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
 * execute_command - Execute a command using fork and execve
 * @args: Argument vector
 * @prog_name: Program name (from av[0])
 * @line_count: Line number (used for errors)
 *
 * Return: Nothing
 */
void execute_command(char **args, char *prog_name, int line_count)
{
    pid_t pid;
    char *cmd_path;

    cmd_path = find_in_path(args[0]);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, args[0]);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(cmd_path);
        return;
    }

    if (pid == 0)
    {
        if (execve(cmd_path, args, environ) == -1)
        {
            perror("execve");
            free(cmd_path);
            exit(127);
        }
    }
    else
    {
        wait(NULL);
        free(cmd_path);
    }
}

/**
 * handle_builtins - Check if a command is a builtin and run it
 * @args: Argument vector
 *
 * Return: 1 if a builtin was executed, -1 if exit, 0 otherwise
 */
int handle_builtins(char **args)
{
    int i;

    if (_strcmp(args[0], "exit") == 0)
    {
        free_args(args);
        return (-1); /* signal to exit */
    }

    if (_strcmp(args[0], "env") == 0)
    {
        for (i = 0; environ[i] != NULL; i++)
        {
            printf("%s\n", environ[i]);
        }
        free_args(args);
        return (1);
    }

    return (0);
}

/**
 * free_args - Free the memory used by arguments
 * @args: Argument vector to free
 *
 * Return: Nothing
 */
void free_args(char **args)
{
    int i = 0;

    if (!args)
        return;

    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

