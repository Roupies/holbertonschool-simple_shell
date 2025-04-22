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
extern int last_exit_status;

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
int command_not_found(char *prog_name, char *command);
int execute_in_fork(char *cmd_path, char **args);
int execute_in_child(char *cmd_path, char **args);
int wait_for_child(pid_t pid, int status, char *cmd_path);


/* builtins.c */
int handle_builtins(char **args);

/* String functions */
char *_strchr(const char *s, int c);
char *_strdup(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n);
char *_strcat(char *dest, const char *src);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

/* path_utils.c */
char *find_in_path(char *command);

#endif /* SHELL_H */

