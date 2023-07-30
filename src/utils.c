#include "utils.h"

void removeSpaces(const char *str_raw, char *str_trimmed)
{
  while (*str_raw != '\0') {
    if (!isspace(*str_raw))
      *str_trimmed++ = *str_raw;

    str_raw++;
  }
  *str_trimmed = '\0';
}
