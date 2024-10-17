/*

sample_main_with_getopt_long.c 
Copyright (C) 1988-2024 by Lane Hensley <https://lanehensley.org>
Repository: <https://github.com/lhensley/toybox>
This file is subject to the MIT License <https://opensource.org/license/mit>

Copyright 1988-2024 Lane Hensley

Permission is hereby granted, free of charge, 
to any person obtaining a copy of this software 
and associated documentation files (the “Software”), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Adapted from: https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
Help: https://linux.die.net/man/3/getopt_long
Help: https://stackoverflow.com/questions/7489093/getopt-long-proper-way-to-use-it

*/

#define _GNU_SOURCE       // For getopt_long
#include <getopt.h>       // For getopt_long
#include <libgen.h>       // For basename()
#include <stdio.h>        // Standard I/O
#include <stdlib.h>       // Standard Library
// #include <string.h>       // Don't recall why this was there!
// #include <unistd.h>       // For access()
#include "lane_stdlib.h"  // Lane Standard Library
// #include "lane_fs.h"      // Lane File System Library

// GLOBAL variables
char *program_version="0.1.0";

int main (int argc, char **argv)
{
  /* Options */
  /* These will vary according to the options defined. */
  static int verbose_flag=0; // A static int variable remains in memory while the program is running.
  static int opt_L=0, opt_V=0, opt_h=0;
  static int opt_a=0, opt_b=0, opt_c=0, opt_d=0, opt_f=0;
  char *arg_c,*arg_d,*arg_f;

  int c;

  while (1)
    {
      /* For more on this structure definition and use, 
          see https://linux.die.net/man/3/getopt_long */
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          {"brief",   no_argument,       &verbose_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"license", no_argument,       0, 'L'},
          {"version", no_argument,       0, 'V'},
          {"add",     no_argument,       0, 'a'},
          {"append",  no_argument,       0, 'b'},
          // We can add multiple long option synonym versions as desired, like these:
          {"create",  required_argument, 0, 'c'},
          {"make",    required_argument, 0, 'c'},
          {"delete",  required_argument, 0, 'd'},
          {"file",    required_argument, 0, 'f'},
          {"help",    no_argument,       0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      /* one colon (:) means previous letter takes an argument. */
      /* two colons (::) means optional argument. */
      c = getopt_long (argc, argv, "LVabc:d:f:h",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0: // Not currently sure what this does. Yet.
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'L':
          opt_L=1;
          break;

        case 'V':
          // printf ("option -f with value `%s'\n", optarg);
          opt_V=1;
          break;

        case 'a':
          // puts ("option -a\n");
          opt_a=1;
          break;

        case 'b':
          // puts ("option -b\n");
          opt_b=1;
          break;

        case 'c':
          // printf ("option -c with value `%s'\n", optarg);
          opt_c=1;
          arg_c=optarg;
          break;

        case 'd':
          // printf ("option -d with value `%s'\n", optarg);
          opt_d=1;
          arg_d=optarg;
          break;

        case 'f':
          // printf ("option -f with value `%s'\n", optarg);
          opt_f=1;
          arg_f=optarg;
          break;

        case 'h':
          // printf ("option -f with value `%s'\n", optarg);
          opt_h=1;
          break;

        case '?':
          /* getopt_long already printed an error message. */
          exit (1);

        default:
          abort ();
        }
    }

// ###########################################################################
// ###  ERROR CHECKING
// ###########################################################################

  if (opt_L) {
    display_license(argv[0]);
    exit(1);
    }

  if (opt_h || opt_V) {
    display_program_info_header (argv[0]);
    if (opt_h) {
      fprintf(stderr,"\nUsage: %s [OPTIONS] ARGS\n\n",basename(argv[0]));
      fprintf(stderr,"This is a demonstration program and template for 'real' programs.\n");
      fprintf(stderr,"It parses and displays flags, options, arguments, and errors you specify.\n\n");
      fprintf(stderr,"Options\n");
      fprintf(stderr,"--brief                    notes but ignores requests for brevity\n");
      fprintf(stderr,"--verbose                  notes but ignores requests for verbosity\n");
      fprintf(stderr,"--add, -a                  notes but ignores option with no argument\n");
      fprintf(stderr,"--append, -b               notes but ignores option with no argument\n");
      fprintf(stderr,"--create=argument, --make=argument, -c argument\n");
      fprintf(stderr,"                           notes but ignores option with argument\n");
      fprintf(stderr,"--delete=argument, -d argument\n");
      fprintf(stderr,"                           notes but ignores option with argument\n");
      fprintf(stderr,"--file=argument, -f argument\n");
      fprintf(stderr,"                           notes but ignores option with argument\n");
      fprintf(stderr,"--license, -L              shows the MIT license\n");
      fprintf(stderr,"--version, -V              shows the version + other info and exits\n");
      fprintf(stderr,"--help, -h (*)             shows this help (* -h is help only on its own)\n");      
      }
    exit(0);
    }

// ###########################################################################
// ###  FROM HERE ON, PUT THE GUTS OF THE PROGRAM IN.
// ###########################################################################

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  if (verbose_flag)
    printf ("verbose flag is set\n");
  if (opt_a)
    printf ("option -a is set\n");
  if (opt_b)
    printf ("option -b is set\n");
  if (opt_c) {
    printf ("option -c is set\n");
    printf (" argument is %s\n",arg_c);
    }
  if (opt_d) {
    printf ("option -d is set\n");
    printf (" argument is %s\n",arg_d);
    }
  if (opt_f) {
    printf ("option -f is set\n");
    printf (" argument is %s\n",arg_f);
    }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
      }

  exit (0);
}

