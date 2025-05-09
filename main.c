#include "shell.h"

int last_exit_status;  /* Variable globale pour stocker le statut de sortie */


/**
 * display_prompt - Print shell prompt
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "(¬‿¬) " ,9);
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

	/* Si la commande est 'exit' */
	if (_strcmp(args[0], "exit") == 0)
	{
		/* Retourner -1 pour signaler que 'exit' a été appelé */
		return (-1);
	}

	/* Si la commande est 'env', on l'affiche */
	if (_strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);  /* Pas un builtin reconnu */
}

/**
 * handle_input - Parse and execute a line of input
 * @line: The input line from the user
 * @av: Argument vector (used for program name in error messages)
 *
 * Return: -1 if "exit" builtin is called to terminate the shell,
 *          0 otherwise
 */
int handle_input(char *line, char **av)
{
	char **args;
	int builtin_result;

	args = parse_line(line);
	if (!args || !args[0])
	{
		free_args(args);
		return (0);
	}

	/* Si l'utilisateur demande le code de sortie $? */
	if (_strcmp(args[0], "$?") == 0)
	{
		printf("%d\n", last_exit_status);
		free_args(args);
		return (0);
	}

	/* Gérer les builtins */
	builtin_result = handle_builtins(args);
	if (builtin_result == -1)
	{
		free_args(args);
		return (-1);  /* Sortir si exit est appelé */
	}
	else if (builtin_result == 1)
	{
		free_args(args);
		return (0);  /* Si un autre builtin est exécuté, on continue */
	}

	/* Exécuter la commande normale et mettre à jour last_exit_status */
	last_exit_status = execute_command(args, av[0]);
	free_args(args);
	return (0);
}

/**
 * main - Entry point of the shell
 * @ac: Argument count (unused)
 * @av: Argument vector (used for program name)
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	(void)ac;

	while (1)
	{
		display_prompt();
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		if (handle_input(line, av) == -1)
			break;
	}

	free(line);

	/* Retourner le statut de sortie de la dernière commande avant exit */
	return (last_exit_status);
}
