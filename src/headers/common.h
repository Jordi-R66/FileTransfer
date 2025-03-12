#pragma once

#ifndef COMMON_HEADER

	#define COMMON_HEADER
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <string.h>

	#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
		/* bool, true and false are keywords.  */
	#else
		#include <stdbool.h>
	#endif

	typedef char* string;

#endif
