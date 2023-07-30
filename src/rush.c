#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
  /* 1000 chars is the maximum input length because of '\0' */

  size_t buffer_size = 1001;
  char *raw_input_buffer = (char *)malloc(buffer_size);

  /* buffer to store input without spaces */
  char *trimmed_input_buffer = (char *)malloc(buffer_size);

  while (1) {
    fputs("> ", stdout);

    /* fgets() reads 1000 characters and adds '\0' character at the end of the string */
    fgets(raw_input_buffer, buffer_size, stdin);

    /* remove spaces from buffer */
    removeSpaces(raw_input_buffer, trimmed_input_buffer);

    if (trimmed_input_buffer[0] == '\0') {
      /* buffer is empty */
      continue;

    } else if (strncmp(trimmed_input_buffer, "exit", 4) == 0) {
      /* exit command */
      free(raw_input_buffer);
      free(trimmed_input_buffer);
      return 0;

    } else {
      fputs("rush: command not found\n", stderr);
    }
  };
}


