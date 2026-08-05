#include "test.h"
#include "helpers.h"
#include "math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
test_fail (double expected, double result)
{
  printf ("\033[31mfail! expected %f, got %f\033[0m\n", expected, result);
}

void
test_pass (void)
{
  printf ("\033[32mpass\033[0m\n");
}

int
run_a_test (char *test, char *exp, double expected)
{
  FILE *fptr = NULL;
  double result = 0;

  printf ("Testing %s (script: %s)...\t\t", test, exp);

  fptr = fopen ("cicalc_script", "w+");

  fprintf (fptr, "%s", exp);

  fclose (fptr);

  fptr = fopen ("cicalc_script", "r");

  result = perform_calculation (fptr, 0);

  if (result == expected)
    {
      test_pass ();
      return 0;
    }
  else
    {
      test_fail (expected, result);
      return 1;
    }
}

int
test_cicalc (void)
{
  int exit_code = 0;

  if (run_a_test ("add", "add 5.5 5.5", 11) != 0)
    {
      exit_code = 1;
    }

  if (run_a_test ("sub", "sub 5.5 .5", 5) != 0)
    {
      exit_code = 1;
    }

  if (run_a_test ("mul", "mul 2.5 2", 5) != 0)
    {
      exit_code = 1;
    }

  if (run_a_test ("mul", "mul 5.5 pi", 5.5 * acos (-1.0)) != 0)
    {
      exit_code = 1;
    }

  if (run_a_test ("div", "div 5 2.5", 2) != 0)
    {
      exit_code = 1;
    }

  if (run_a_test ("nrt", "nrt 25 2", 5) != 0)
    {
      exit_code = 1;
    }

  if (run_a_test ("pow", "pow 5 2", 25) != 0)
    {
      exit_code = 1;
    }

  remove ("cicalc_script");

  return exit_code;
}
