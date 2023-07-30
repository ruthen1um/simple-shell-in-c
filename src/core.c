#include "core.h"
#include "builtin.h"

void rush_loop()
{
  const int max_line = 1024;
  const int max_tokens = 256;
  char *input_buffer = (char *)malloc(sizeof(char) * max_line);
  char **tokens = (char **)malloc(sizeof(char *) * max_tokens);
  char *token;
  int status = 0;
  int p = 0;
  char delims[] = " \t\n\v\f\r";

  do {
    fputs("> ", stdout);

    /* empty buffers */
    memset(input_buffer, '\0', strlen(input_buffer));
    memset(tokens, '\0', strlen(input_buffer));

    /* fgets() reads (max_line - 1) characters and adds '\0' character at the end of the string */
    fgets(input_buffer, max_line, stdin);

    p = 0;

    token = strtok(input_buffer, delims);

    while (token != NULL) {
      tokens[p++] = token;
      token = strtok(NULL, delims);
    }

    tokens[p] = NULL;

    if (tokens[0] == NULL) {
      /* buffer is empty */
      continue;
    }


    for (int i = 0; i < sizeof(rush_builtins) / sizeof(*rush_builtins); i++) {
      if (strncmp(tokens[0], rush_builtins[i].name, strlen(tokens[0])) == 0) {
        status = rush_builtins[i].func(tokens + 1);
      }
    }


  } while (!status);
}
