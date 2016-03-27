#include <stdio.h>
#include <string.h>

void err_out(const char *reason)
{
  char stderr[50];
  sprintf(stderr, "Error: %s.\n", reason);
  throw stderr;
}

void err_sys(const char *function)
{
  throw strerror(function);
}
