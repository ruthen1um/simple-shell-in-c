#include "builtin.h"

rush_builtin rush_builtins[] = {
    { "exit", &rush_exit },
};

int rush_exit(char **args)
{
    return 1;
}
