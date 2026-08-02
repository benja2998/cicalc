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

  printf ("Testing add...\t\t");

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
      printf ("\033[32mpass\033[0m\n");
    }
  else
    {
      printf ("\033[31mfail! expected 11.000000, got %s\033[0m\n", s);
    }

  printf ("Testing sub...\t\t");

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
      printf ("\033[32mpass\033[0m\n");
    }
  else
    {
      printf ("\033[31mfail! expected 5.000000, got %s\033[0m\n", s);
    }

  printf ("Testing mul...\t\t");

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
      printf ("\033[32mpass\033[0m\n");
    }
  else
    {
      printf ("\033[31mfail! expected 5.000000, got %s\033[0m\n", s);
    }

  printf ("Testing div...\t\t");

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
      printf ("\033[32mpass\033[0m\n");
    }
  else
    {
      printf ("\033[31mfail! expected 2.000000, got %s\033[0m\n", s);
    }

  printf ("Testing nrt...\t\t");

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
      printf ("\033[32mpass\033[0m\n");
    }
  else
    {
      printf ("\033[31mfail! expected 5.000000, got %s\033[0m\n", s);
    }

  printf ("Testing pow...\t\t");

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
      printf ("\033[32mpass\033[0m\n");
    }
  else
    {
      printf ("\033[31mfail! expected 25.000000, got %s\033[0m\n", s);
    }

  return exit_code;
}
