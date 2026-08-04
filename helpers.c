#include "helpers.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>

FILE *
handle_args (char *argv1, FILE *stdin_or_f, char *argv0)
{
  if (strcmp (argv1, "--test") == 0)
    {
      int result = test_cicalc (argv0);

      if (result == 1)
        {
          fprintf (stderr, "You've found one or more bugs!\n"
                           "If you're a user, report these at:\n"
                           "https://codeberg.org/benja2998/cicalc/issues\n");
        }

      exit (result);
    }
  else if (strcmp (argv1, "--help") == 0)
    {
      printf ("Usage: %s [filename or option]\n"
              "Options:\n"
              "--help\t\tshow this help message\n"
              "--test\t\trun tests\n",
              argv0);
      exit (0);
    }
  else
    {
      stdin_or_f = fopen (argv1, "r");
      if (stdin_or_f == NULL)
        {
          perror ("Failed to open file");
          exit (1);
        }
    }
  return stdin_or_f;
}
