#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* main.c */
void display_prompt(void);

/* parser.c */
char **parse_line(char *line);
void free_args(char **args);

/* executor.c */
void execute_command(char **args, char *prog_name, int line_count);

/* utils.c */
int _strcmp(char *s1, char *s2);
void _strcpy(char *dest, const char *src);

/* builtins.c */
int handle_builtins(char **args);

char *find_in_path(char *command);


#endif /* SHELL_H */

