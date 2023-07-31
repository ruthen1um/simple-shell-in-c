#include "builtin.h"

rush_builtin rush_builtins[1] = {
    { "exit", &rush_exit },
};

int rush_exit(char *args[])
{
    // special return value indicating that shell must terminate with success
    return -1;
}
