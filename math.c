#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double
token_to_number (double number, char *ptr, char *token)
{
  if (strcmp (token, "pi") == 0)
    {
      number = acos (-1.0);
    }
  else
    {
      number = strtod (token, &ptr);
    }

  if (errno == ERANGE)
    {
      fprintf (stderr, "[ERROR]: out of range\n");
      exit (1);
    }

  if (token == ptr)
    {
      fprintf (stderr, "[ERROR]: bad input\n");
      exit (1);
    }

  return number;
}
