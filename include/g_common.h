/*******************************************************************************

Copyright (C) 2018, Ryan McClue

g_common.h
	"Common macro definitions."

GAME:
	"Cross platform 2D SDL game."

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

#define GAME_VERSION "3.11.1"
#define GAME_BUG_REPORT_ADDRESS "<git-link>"
#define GAME_NAME "Game"
#define GAME_UNAME "GAME"
#define GAME_LNAME "game"
#define GAME_BINARY_STRING "game"
#define GAME_DESCRIPTION "Cross platform 2D SDL game."
#define GAME_CREATOR "Ryan McClue"

/******************************************************************************
 * COMMON MACROS
 *****************************************************************************/

#define GAME_TO_STRING(val)	#val
#define GAME_STRINGIFY(str)	GAME_TO_STRING(str)

#define GAME_INTERNAL static
#define GAME_LOCAL_PERSIST static
#define GAME_DEFAULT_INITIALISER {0,}

#define GAME_LEAVE(func_leave_code) \
	do { \
		leave_code = func_leave_code; \
		goto __leave; \
	} while (0);

#define GAME_NO_DEFAULT_CASE

#if GAME_BUILD_MODE_DEBUG
#ifdef _MSC_VER
#include <intrin.h>
#else
// ~/.gdbinit --> break __debugbreak
#include <stdlib.h>
static inline void __debugbreak(void) { exit(EXIT_FAILURE); }
#endif
#define GAME_BREAKPOINT() __debugbreak()
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
#define GAME_ALIGN(val) __attribute__((aligned(val)))
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
#define GAME_ALIGN(val) __declspec(align(val))
#define GAME_DEPRECATED __declspec(deprecated)
#else
#define GAME_ALIGN(val)
#define GAME_PURE
#define GAME_CONST
#define GAME_COLD
#define GAME_HOT
#define GAME_CHECK
#define GAME_DEPRECATED
#define GAME_USED
#define GAME_UNUSED
#define GAME_PACKED
#define GAME_LIKELY(val)
#define GAME_UNLIKELY(val)
#define GAME_DESIGNATED
#define GAME_FLATTEN
#endif

#endif
