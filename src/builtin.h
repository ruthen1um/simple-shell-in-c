#ifndef BUILTIN_H
#define BUILTIN_H

typedef struct {
    char *name;
    int (*func)(char *args[]);
} rush_builtin;

extern rush_builtin rush_builtins[];

int rush_exit(char **args);

#endif
