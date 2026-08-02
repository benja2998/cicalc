#include "test.h"
#include <stdlib.h>

int
test_cicalc (void)
{
  char s[1024];
  FILE *fptr;
  int add_failed = 0;
  int sub_failed = 0;
  int mul_failed = 0;
  int div_failed = 0;
  int nrt_failed = 0;
  int pow_failed = 0;
  int exit_code = 0;

  printf ("Testing addition... ");

  system ("echo \"add 5.5 5.5\" | ./cicalc > cicalc.results_test");

  fptr = fopen ("cicalc.results_test", "r");
  if (fptr == NULL)
    {
      fprintf (stderr, "[ERROR]: file can't be opened");
      return 1;
    }

  fscanf (fptr, "%[^\n]", s);
  if (strcmp (s, "11.000000") != 0)
    {
      add_failed = 1;
      exit_code = 1;
    }

  if (add_failed == 0)
    {
      printf ("pass\n");
    }
  else
    {
      printf ("fail!\n");
    }

  printf ("Testing subtraction... ");

  system ("echo \"sub 5.5 .5\" | ./cicalc > cicalc.results_test");

  fptr = fopen ("cicalc.results_test", "r");
  if (fptr == NULL)
    {
      fprintf (stderr, "[ERROR]: file can't be opened");
      return 1;
    }

  fscanf (fptr, "%[^\n]", s);
  if (strcmp (s, "5.000000") != 0)
    {
      sub_failed = 1;
      exit_code = 1;
    }

  if (sub_failed == 0)
    {
      printf ("pass\n");
    }
  else
    {
      printf ("fail!\n");
    }

  printf ("Testing multiplication... ");

  system ("echo \"mul 2.5 2\" | ./cicalc > cicalc.results_test");

  fptr = fopen ("cicalc.results_test", "r");
  if (fptr == NULL)
    {
      fprintf (stderr, "[ERROR]: file can't be opened");
      return 1;
    }

  fscanf (fptr, "%[^\n]", s);
  if (strcmp (s, "5.000000") != 0)
    {
      mul_failed = 1;
      exit_code = 1;
    }

  if (mul_failed == 0)
    {
      printf ("pass\n");
    }
  else
    {
      printf ("fail!\n");
    }

  printf ("Testing division... ");

  system ("echo \"div 5 2.5\" | ./cicalc > cicalc.results_test");

  fptr = fopen ("cicalc.results_test", "r");
  if (fptr == NULL)
    {
      fprintf (stderr, "[ERROR]: file can't be opened");
      return 1;
    }

  fscanf (fptr, "%[^\n]", s);
  if (strcmp (s, "2.000000") != 0)
    {
      div_failed = 1;
      exit_code = 1;
    }

  if (div_failed == 0)
    {
      printf ("pass\n");
    }
  else
    {
      printf ("fail!\n");
    }

  printf ("Testing N root... ");

  system ("echo \"nrt 25 2\" | ./cicalc > cicalc.results_test");

  fptr = fopen ("cicalc.results_test", "r");
  if (fptr == NULL)
    {
      fprintf (stderr, "[ERROR]: file can't be opened");
      return 1;
    }

  fscanf (fptr, "%[^\n]", s);
  if (strcmp (s, "5.000000") != 0)
    {
      nrt_failed = 1;
      exit_code = 1;
    }

  if (nrt_failed == 0)
    {
      printf ("pass\n");
    }
  else
    {
      printf ("fail!\n");
    }

  printf ("Testing exponentiation... ");

  system ("echo \"pow 5 2\" | ./cicalc > cicalc.results_test");

  fptr = fopen ("cicalc.results_test", "r");
  if (fptr == NULL)
    {
      fprintf (stderr, "[ERROR]: file can't be opened");
      return 1;
    }

  fscanf (fptr, "%[^\n]", s);
  if (strcmp (s, "25.000000") != 0)
    {
      pow_failed = 1;
      exit_code = 1;
    }

  if (pow_failed == 0)
    {
      printf ("pass\n");
    }
  else
    {
      printf ("fail!\n");
    }

  return exit_code;
}
