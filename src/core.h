#ifndef CORE_H
#define CORE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void rush_loop();
void rush_prompt();
char *rush_read_line();
char **rush_tokenize(char *line);
int rush_execute(char **tokens);

#endif
