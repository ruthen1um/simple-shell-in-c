#ifndef _BUILTIN_H_
#define _BUILTIN_H_

typedef struct {
    char *name;
    int (*func)(char **args);
} rush_builtin;

extern rush_builtin rush_builtins[];

int rush_exit(char **args);

#endif /* _BUILTIN_H_ */
