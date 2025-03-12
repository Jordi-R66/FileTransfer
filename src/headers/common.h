#pragma once

#ifndef COMMON_HEADER

#define COMMON_HEADER
#include <stdio.h>
#include <stdlib.h>

#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
/* bool, true and false are keywords.  */
#else
#include <stdbool.h>
#endif

#endif
