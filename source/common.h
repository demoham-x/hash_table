/**
 * common.h
 * Common Header Files to be included
 */
#ifndef COMMON_H
#define COMMON_H

/* Standard library includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include <time.h>

/* Other commonly used headers */
#include <errno.h>
#include <limits.h>
#ifdef _WIN32
#include <windows.h>
#endif

/* Add more includes as needed for the project */

/* Type definitions for standard data types */
typedef unsigned char      UCHAR;
typedef unsigned short     USHORT;
typedef unsigned int       UINT;
typedef unsigned long      ULONG;
typedef unsigned long long ULONG_LONG;

#ifndef _WIN32
typedef char               INT8;
#endif
typedef char               CHAR;
typedef unsigned char      UINT8;
typedef short              INT16;
typedef unsigned short     UINT16;
typedef int                INT32;
typedef unsigned int       UINT32;
typedef long long          INT64;
typedef unsigned long long UINT64;

typedef float              FLOAT;
typedef double             DOUBLE;

typedef UINT16             API_RESULT;


/* Macros For Results */
#define API_SUCCESS                  0x0000
#define API_FAILURE                  0xFFFF

/* Macros For True/false */
#ifndef _WIN32
#define TRUE                         1U
#define FALSE                        0U
#endif

/* Macros for memory allocation functions */
#define MALLOC(size)       malloc((size_t)size)
#define CALLOC(num, size)  calloc((size_t)num, (size_t)size)
#define REALLOC(ptr, size) realloc(ptr, (size_t)size)
#define FREE(ptr)          free(ptr)

/* Typedefs for keywords */
#define DECL_CONST  const
#define DECL_STATIC static

/* console in and out defines */
#define CONSOLE_IN(...)     scanf(__VA_ARGS__)
#define CONSOLE_OUT(...)    printf(__VA_ARGS__)

#endif /* COMMON_H */