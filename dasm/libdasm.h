/*

Copyright 2016 Bobby Crawford (ozdevguy) | ozdevguy@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

========================================================================

The Ditto Virtual Machine | Ditto Assembler (dasm)

=========================================================================
Revision History

Written: March 2016 -> Bobby Crawford (ozdevguy)
Last Revision: N/A

=========================================================================

libdasm.h

The Grand Kahuna of dasm. libdasm.h is the main header that links everything together.

*/

typedef unsigned char byte;

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libdasm/dictionary.h"
#include "libdasm/error.h"
#include "libdasm/input.h"
//#include "libdasm/data.h"
#include "libdasm/tracker.h"
#include "libdasm/parser.h"