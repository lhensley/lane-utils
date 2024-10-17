/*

lane_stdlib.c
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

*/

#include <stdio.h>          // Standard I/O
#include <stdlib.h>         // Standard Library
#include <libgen.h>         // For basename()
#include "lane_stdlib.h"    // For Lane Standard Library

// GLOBAL variables
char *LGH_author_name="Lane Hensley"; // Also update in license text below.
char *LGH_copyright_year="1988-2024"; // Also update in license text below.
char *LGH_mit_license_link="<https://opensource.org/license/mit>";
char *LGH_personal_website="<https://lanehensley.org>";
char *LGH_github_website="<https://github.com/lhensley/toybox>";
char *LGH_mit_license_text = 
    "Copyright 1988-2024 Lane Hensley\n\n \
    Permission is hereby granted, free of charge,\n \
    to any person obtaining a copy of this software\n \
    and associated documentation files (the “Software”),\n \
    to deal in the Software without restriction,\n \
    including without limitation the rights to use, copy, modify, merge,\n \
    publish, distribute, sublicense, and/or sell copies of the Software,\n \
    and to permit persons to whom the Software is furnished to do so,\n \
    subject to the following conditions:\n\n \
    The above copyright notice and this permission notice shall be included\n \
    in all copies or substantial portions of the Software.\n\n \
    THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,\n \
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n \
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n \
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,\n \
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n \
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE\n \
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.";

void display_license (char *this_program) {
    display_program_info_header (this_program);
    fprintf(stderr,"\n%s\n",LGH_mit_license_text);
    }

void display_program_info_header (char *this_program) {
    extern char *program_version;

    fprintf(stderr,"%s %s\n",basename(this_program),program_version);
    fprintf(stderr,"Copyright (C) %s by %s %s %s\n",
        LGH_copyright_year,LGH_author_name,LGH_github_website,LGH_personal_website);
    fprintf(stderr,"Distributed under the MIT License %s\n",LGH_mit_license_link);
    fprintf(stderr,"To display the license, use %s -L\n",basename(this_program));
    }

