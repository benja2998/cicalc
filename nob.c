#define NOB_IMPLEMENTATION
#include "nob.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      puts ("Usage: ./nob [build/install-sys/install-user]");
      return 1;
    }

  NOB_GO_REBUILD_URSELF (argc, argv);

  if (strcmp (argv[1], "install-sys") == 0)
    {
      char buf[1024];
      char *cwd = getcwd (buf, 1023);
      char cicalc_bin[1024];
      int written1 = snprintf (cicalc_bin, 1023, "%s/cicalc", buf);

      char cicalc_man[1024];
      int written2 = snprintf (cicalc_man, 1023, "%s/cicalc.1", buf);

      if (written1 < 0 || written2 < 0)
        {
          perror ("Error");
          return 1;
        }

      if (access (cicalc_bin, F_OK) != 0 || access (cicalc_man, F_OK) != 0)
        {
          return 1;
        }
      Nob_Cmd cmd1 = { 0 };
      nob_cmd_append (&cmd1, "ln", "-sf", cicalc_bin, "/usr/local/bin/cicalc");
      if (!nob_cmd_run (&cmd1))
        return 1;
      Nob_Cmd cmd2 = { 0 };
      nob_cmd_append (&cmd2, "ln", "-sf", cicalc_man,
                      "/usr/local/share/man/man1/cicalc.1");
      if (!nob_cmd_run (&cmd2))
        return 1;
    }
  else if (strcmp (argv[1], "install-user") == 0)
    {
      char buf[1024];
      char *cwd = getcwd (buf, 1023);
      char cicalc_bin[1024];
      int written1 = snprintf (cicalc_bin, 1023, "%s/cicalc", buf);

      char cicalc_man[1024];
      int written2 = snprintf (cicalc_man, 1023, "%s/cicalc.1", buf);

      char *home = getenv ("HOME");
      char install_cb[1024];
      int written3 = snprintf (install_cb, 1023, "%s/.local/bin/cicalc", home);

      char install_cm[1024];
      int written4 = snprintf (install_cm, 1023,
                               "%s/.local/share/man/man1/cicalc.1", home);

      if (written1 < 0 || written2 < 0 || written3 < 0 || written4 < 0)
        {
          perror ("Error");
          return 1;
        }

      if (access (cicalc_bin, F_OK) != 0 || access (cicalc_man, F_OK) != 0)
        {
          return 1;
        }
      Nob_Cmd cmd1 = { 0 };
      nob_cmd_append (&cmd1, "ln", "-sf", cicalc_bin, install_cb);
      if (!nob_cmd_run (&cmd1))
        return 1;
      Nob_Cmd cmd2 = { 0 };
      nob_cmd_append (&cmd2, "ln", "-sf", cicalc_man, install_cm);
      if (!nob_cmd_run (&cmd2))
        return 1;
    }
  else if (strcmp (argv[1], "build") == 0)
    {
      Nob_Cmd cmd1 = { 0 };
      nob_cmd_append (&cmd1, "clang-format", "-i", "helpers.c", "helpers.h",
                      "main.c", "math.c", "math.h", "nob.c", "one.c", "test.c",
                      "test.h");
      if (!nob_cmd_run (&cmd1))
        return 1;
      Nob_Cmd cmd2 = { 0 };
      nob_cmd_append (&cmd2, "cc", "-Wall", "-Wextra", "-lm", "-pedantic",
                      "-Werror", "-std=gnu99", "-march=native", "-O3", "-o",
                      "cicalc", "one.c");
      if (!nob_cmd_run (&cmd2))
        return 1;
      Nob_Cmd cmd3 = { 0 };
      nob_cmd_append (&cmd3, "./cicalc", "--test");
      if (!nob_cmd_run (&cmd3))
        return 1;
    }

  return 0;
}
