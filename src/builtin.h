#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
  char *name;
  int (*func)(char *args[]);
} rush_builtin;

extern rush_builtin rush_builtins[1];

int rush_exit(char *args[]);

#endif
