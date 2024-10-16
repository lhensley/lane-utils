/*

proto_parse_plex_filename.c 
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
#include <limits.h>       // Defining max length for pathname
// #include <sys/syslimits.h>
#include <stdio.h>        // Standard I/O
#include <stdlib.h>       // Standard Library
#include <string.h>       // For string testing and adapting
#include <unistd.h>       // For access()
#include "lane_stdlib.h"  // Lane Standard Library
#include "lane_fs.h"      // Lane File System Library

// GLOBAL variables
char *program_version="0.1.0";

int main (int argc, char **argv)
{
  /* Options */
  /* These will vary according to the options defined. */
  static int opt_L=0, opt_V=0, opt_h=0;

  int c;

  while (1)
    {
      /* For more on this structure definition and use, 
          see https://linux.die.net/man/3/getopt_long */
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"license", no_argument,       0, 'L'},
          {"version", no_argument,       0, 'V'},
          {"help",    no_argument,       0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      /* one colon (:) means previous letter takes an argument. */
      /* two colons (::) means optional argument. */
      c = getopt_long (argc, argv, "LVh",
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
          opt_V=1;
          break;

        case 'h':
          opt_h=1;
          break;

        case '?':
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
      fprintf(stderr,"\nUsage: %s [OPTIONS] [path/]filename\n\n",basename(argv[0]));
      fprintf(stderr,"Parses and displays Plex filenames.\n\n");
      fprintf(stderr,"Options\n");
      fprintf(stderr,"--license, -L              shows the MIT license\n");
      fprintf(stderr,"--version, -V              shows the version + other info and exits\n");
      fprintf(stderr,"--help, -h (*)             shows this help (* -h is help only on its own)\n");      
      }
    exit(1);
    }

  if ((argc-optind)<1) {
    fprintf(stderr,"ERROR: No argument speficied.\n");
    exit(1);
    }

  if ((argc-optind)>1) {
    fprintf(stderr,"ERROR: Too many arguments.\n");
    exit(1);
    }

  if (strlen(argv[(argc-optind)])>=PATH_MAX) {
    fprintf(stderr,"ERROR: Pathname is %lu characters, and the max allowed is %d.\n",
                strlen(argv[(argc-optind)]),PATH_MAX-1);
    exit(1);
    }

  /*
  
  if (!fs_isfile(argv[(argc-optind)])) {
    fprintf(stderr,"ERROR: %s is not a file.\n",argv[(argc-optind)]);
    exit(1);
    }

  if (!fs_isreadable(argv[(argc-optind)])) {
    fprintf(stderr,"ERROR: %s is not readable.\n",argv[(argc-optind)]);
    exit(1);
    }

  */

// ###########################################################################
// ###  FROM HERE ON, PUT THE GUTS OF THE PROGRAM IN.
// ###########################################################################

  // NEED TO DETERMINE WHETHER INPUT FILE EXISTS
  printf("Input file: %s\n",basename(argv[(argc-optind)]));

  exit (0);
}
