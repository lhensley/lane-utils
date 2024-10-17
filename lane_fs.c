/*

lane_fs.c 
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

#include <libgen.h> // For basename()
#include <stdio.h>  // Standard I/O
#include <stdlib.h> // Standard Libraries
#include <unistd.h> // For access()
#include "lane_fs.h"

int fs_isfile (char *pathname) {
    return (!access(pathname, F_OK));
    }

int fs_isreadable (char *pathname) {
    return (!access(pathname, R_OK));
    }
