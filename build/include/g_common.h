/*******************************************************************************

Copyright (C) 2018, 

g_common.h
	"Common macro definitions."

GAME:
	""

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#ifndef __common_h__
#define __common_h__

#include <stdbool.h>
#include <stdint.h>
#include <signal.h>

/******************************************************************************
 * CMAKE DEFINITIONS
 *****************************************************************************/

/* #undef GAME_VERSION */
/* #undef GAME_BUG_REPORT_ADDRESS */
/* #undef GAME_NAME */
/* #undef GAME_BINARY_STRING */
/* #undef GAME_DESCRIPTION */
/* #undef GAME_CREATOR */

/******************************************************************************
 * COMMON MACROS
 *****************************************************************************/

#define GAME_TO_STRING(val)	#val
#define GAME_STRINGIFY(str)	GAME_TO_STRING(str)

#define GAME_INTERNAL static
#define GAME_LOCAL_PERSIST static
#define GAME_DEFAULT_INITIALISER {0}

#define GAME_LEAVE(func_leave_code) \
	do { \
		leave_code = func_leave_code; \
		goto __leave; \
	} while (0);

#define GAME_NO_DEFAULT_CASE
#if GAME_BUILD_MODE_DEBUG
#define GAME_BREAKPOINT() raise(SIGABRT)
#else
#define GAME_BREAKPOINT() (void)0
#endif

/******************************************************************************
 * COMMON TYPEDEFS
 *****************************************************************************/

typedef float real32;
typedef double real64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

/******************************************************************************
 * COMPILER VERSION DETECTION 
 *****************************************************************************/

#if defined(__GNUC__)
#define GAME_COMPILER "gcc-"GAME_STRINGIFY(__GNUC__)"." \
	GAME_STRINGIFY(__GNUC_MINOR__)"." \
	GAME_STRINGIFY(__GNUC_PATCHLEVEL__)
#elif defined(__llvm__)
#define GAME_COMPILER "llvm-"GAME_STRINGIFY(__clang_major__)"." \
		GAME_STRINGIFY(__clang_minor__)"." \
		GAME_STRINGIFY(__clang_patchlevel__)
#elif defined(_MSC_VER)
#if _MSC_VER <= 1500
#define GAME_COMPILER "MSVC 2008"
#elif _MSC_VER <= 1600
#define GAME_COMPILER "MSVC 2010"
#elif _MSC_VER <= 1700
#define GAME_COMPILER "MSVC 2012"
#elif _MSC_VER <= 1800
#define GAME_COMPILER "MSVC 2013"
#elif _MSC_VER <= 1900
#define GAME_COMPILER "MSVC 2015"
#elif _MSC_VER <= 1912
#define GAME_COMPILER "MSVC 2017"
#endif
#else
#define GAME_COMPILER "Unsupported Compiler"
#endif

/******************************************************************************
 * COMPILER EXTENSIONS
 *****************************************************************************/

#if defined(__GNUC__) || defined(__llvm__) 
#define GAME_ALIGN
#define GAME_PURE __attribute__((pure))
#define GAME_CONST __attribute__((const))
#define GAME_COLD __attribute__((cold))
#define GAME_HOT __attribute__((hot))
#define GAME_CHECK __attribute__((warn_unused_result))
#define GAME_DEPRECATED __attribute__((deprecated))
#define GAME_USED __attribute__((used))
#define GAME_UNUSED __attribute__((unused))
#define GAME_PACKED __attribute__((packed))
#define GAME_LIKELY(val) __builtin_expect(!!(val), 1)
#define GAME_UNLIKELY(val) __builtin_expect(!!(val), 0)
#define GAME_DESIGNATED __attribute__((designated_init))
#define GAME_FLATTEN __attribute__((flatten))
#elif defined (_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#define inline __inline
#define restrict __restrict
#define GAME_ALIGN
#define GAME_DEPRECATED
#else
#define GAME_ALIGN
#define GAME_DEPRECATED
#endif

#endif
