#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error(const char* error_message, ...) {
  va_list args;
  va_start(args, error_message);

  fprintf(stderr, "\033[1;31merror: \033[0;0m");
  vfprintf(stderr, error_message, args);
  fprintf(stderr, ".\n");

  va_end(args);

  exit(1);
}
