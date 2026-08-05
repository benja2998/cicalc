#include "math.h"
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

double
perform_calculation (FILE *stdin_or_f, int print)
{
  int waitingtoadd = 0;
  int waitingtosub = 0;
  int waitingtomul = 0;
  int waitingtodiv = 0;
  int waitingtonrt = 0;
  int waitingtopow = 0;
  double topow = 0;
  double tonrt = 0;
  double result = nan ("");

  char input[2048];
  if (fgets (input, sizeof (input), stdin_or_f) == NULL)
    {
      return 1;
    }

  fflush (stdout);

  char *token = strtok (input, " \n\r");

  while (token != NULL)
    {
      char *ptr = NULL;
      double number = 0;

      if (strcmp (token, "quit") == 0)
        {
          exit (0);
        }
      else if (strcmp (token, "add") == 0)
        {
          // next numbers will be added one by one
          waitingtoadd = 1;
        }
      else if (strcmp (token, "sub") == 0)
        {
          // next numbers will be substracted one by one
          waitingtosub = 1;
        }
      else if (strcmp (token, "mul") == 0)
        {
          // next numbers will be multiplied one by one
          waitingtomul = 1;
        }
      else if (strcmp (token, "div") == 0)
        {
          // next numbers will be divided one by one
          waitingtodiv = 1;
        }
      else if (strcmp (token, "nrt") == 0)
        {
          waitingtonrt = 1;
        }
      else if (strcmp (token, "pow") == 0)
        {
          waitingtopow = 1;
        }
      else
        {
          number = token_to_number (number, ptr, token);

          if (waitingtoadd == 1)
            {
              if (isnan (result))
                {
                  result = 0;
                }
              result = result + number;
            }
          else if (waitingtosub == 1)
            {
              if (isnan (result))
                {
                  result = 0;
                }
              if (result == 0)
                {
                  result = number;
                }
              else
                {
                  result = result - number;
                }
            }
          else if (waitingtomul == 1)
            {
              if (result == 0 || isnan (result))
                {
                  result = number;
                }
              else
                {
                  result = result * number;
                }
            }
          else if (waitingtodiv == 1)
            {
              if (result == 0 || isnan (result))
                {
                  result = number;
                }
              else
                {
                  result = result / number;
                }
            }
          else if (waitingtonrt == 1)
            {
              tonrt = number;
              waitingtonrt = 2;
            }
          else if (waitingtonrt == 2)
            {
              result = pow (tonrt, 1.0 / number);
            }
          else if (waitingtopow == 1)
            {
              topow = number;
              waitingtopow = 2;
            }
          else if (waitingtopow == 2)
            {
              result = pow (topow, number);
            }
          else
            {
              fprintf (stderr, "[ERROR]: bad input\n");
              exit (1);
            }
        }

      token = strtok (NULL, " \n\r");
    }

  switch (print)
    {
    case 0:
      if (feof (stdin_or_f) != 0)
        {
          return result;
        }
      else
        {
          return result;
        }
      break;
    case 1:
      if (isnan (result) == 0)
        {
          printf ("%f\n", result);
        }

      if (feof (stdin_or_f) != 0)
        {
          exit (0);
        }
      break;
    }
  return result;
}
