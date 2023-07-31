#ifndef CORE_H
#define CORE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int rush_loop();
void print_prompt();
void read_input(char *buffer, int size);
void tokenize(char *buffer, char *token_buffer[], int size);
int parse(char *token_buffer[]);

#endif
