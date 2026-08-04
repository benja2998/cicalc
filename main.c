/*
  cicalc - C Interactive CALCulator
  Copyright (C) 2026 benja2998
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "math.h"
#include "test.h"
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char **argv)
{
  FILE *stdin_or_f;
  if (argc >= 2)
    {
      if (strcmp (argv[1], "--test") == 0)
        {
          int result = test_cicalc (argv[0]);

          if (result == 1)
            {
              fprintf (stderr,
                       "You've found one or more bugs!\n"
                       "If you're a user, report these at:\n"
                       "https://codeberg.org/benja2998/cicalc/issues\n");
            }

          return result;
        }
      else if (strcmp (argv[1], "--help") == 0)
        {
          printf ("Usage: %s [filename or option]\n"
                  "Options:\n"
                  "--help\t\tshow this help message\n"
                  "--test\t\trun tests\n",
                  argv[0]);
          return 0;
        }
      else
        {
          stdin_or_f = fopen (argv[1], "r");
          if (stdin_or_f == NULL)
            {
              perror ("Failed to open file");
              return 1;
            }
        }
    }
  else
    {
      stdin_or_f = stdin;
    }
  while (true)
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
          return 0;
        }

      fflush (stdout);

      char *token = strtok (input, " \n\r");

      while (token != NULL)
        {
          char *ptr = NULL;
          double number = 0;

          if (strcmp (token, "quit") == 0)
            {
              return 0;
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
                  return 1;
                }
            }

          token = strtok (NULL, " \n\r");
        }

      if (isnan (result) == 0)
        {
          printf ("%f\n", result);
        }

      if (feof (stdin_or_f))
        {
          return 0;
        }
    }
  return 0;
}
