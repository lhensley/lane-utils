/*

Adapted from: https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
Help: https://linux.die.net/man/3/getopt_long
Help: https://stackoverflow.com/questions/7489093/getopt-long-proper-way-to-use-it

*/

#define _GNU_SOURCE
#include <getopt.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Set my version info */
char copyright_year[]="1988-2024";
char program_author[]="Lane Hensley";
char program_version[]="0.1.0";
char mit_license_link[]="<https://opensource.org/license/mit>";
char personal_website[]="<https://lanehensley.org>";
char github_website[]="<https://github.com/lhensley/toybox>";

/* Options */
/* These will vary according to the options defined. */
static int verbose_flag=0; // A static int variable remains in memory while the program is running.
static int opt_V=0, opt_h=0;
static int opt_a=0, opt_b=0, opt_c=0, opt_d=0, opt_f=0;
char *arg_c,*arg_d,*arg_f;

int main (int argc, char **argv)
{
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
      c = getopt_long (argc, argv, "Vabc:d:f:ho::",
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
          // break;

        default:
          abort ();
        }
    }

/* ###########################################################################
###  EDIT THIS PERSION FOR HELP AND VERSION
########################################################################### */

  if (opt_h || opt_V) {
    fprintf(stderr,"%s %s\n",basename(argv[0]),program_version);
    fprintf(stderr,"Copyright (C) %s by %s %s\n",copyright_year,program_author,mit_license_link);
    fprintf(stderr,"%s %s\n",github_website,personal_website);
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
      fprintf(stderr,"--version, -V              prints the version + other info and exits\n");
      fprintf(stderr,"--help, -h (*)             shows this help (* -h is help only on its own)\n");      
      }
    exit(0);
    }

/* ###########################################################################
###  FROM HERE ON, PUT THE GUTS OF THE PROGRAM IN.
########################################################################### */

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

