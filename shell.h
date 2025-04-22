#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <signal.h>

extern char **environ;

/* main.c */
void display_prompt(void);
void sigint_handler(int sig);
int handle_input(char *line, char **av);
void handle_signal(int sig);

/* parser.c */
char **parse_line(char *line);
void free_args(char **args);

/* executor.c */
int execute_command(char **args, char *prog_name);
extern int last_exit_status;
char *_get_path(void);
char *create_full_path(char *path, char *command);
char *find_in_path(char *command);

/* builtins.c */
int handle_builtins(char **args);

char *find_in_path(char *command);

/* String functions */
char *_strchr(const char *s, int c);
char *_strdup(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n);
char *_strcat(char *dest, const char *src);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

#endif /* SHELL_H */
