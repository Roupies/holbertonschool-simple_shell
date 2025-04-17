#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void); /* boucle principal */

char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);

#endif
