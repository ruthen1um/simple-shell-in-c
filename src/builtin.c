#include "builtin.h"

rush_builtin rush_builtins[1] = {
  { "exit", &rush_exit },
};

int rush_exit(char *args[])
{
  exit(EXIT_SUCCESS);
}
