/* config.h.  Generated from config.h.cmake by CMake for OpenMD  */
#ifndef __CONFIG_H
#define __CONFIG_H

#define OPENMD_VERSION_MAJOR "2"
#define OPENMD_VERSION_MINOR "5"
#define OPENMD_VERSION_TINY  "0"

#define MK_STR(s) # s
#define STR_DEFINE(t, s) t = MK_STR(s)

#ifdef __EMSCRIPTEN__	
#define FRC_PATH /FRC_ROOT
#else
#define FRC_PATH /usr/local/openmd/forceFields
#endif

/* Is defined if OpenMD should be compiled with single precision arithmetic. */
/* #undef SINGLE_PRECISION */

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#pragma warning( disable : 4996 )
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#ifdef WIN32
#include "utils/wingetopt.h"
#else
#include <getopt.h>
#endif

/* Is defined if the qhull library is available. */
#define DISABLE_QHULL 1
/* #undef HAVE_QHULL */
/* #undef HAVE_QHULL_REENTRANT */
/* #undef HAVE_QHULL_2011 */
#ifdef DISABLE_QHULL
#undef HAVE_QHULL
#endif

/* have <conio.h> */
/* #undef HAVE_CONIO_H */

/* have symbol strncasecmp */
#define HAVE_STRNCASECMP 1

/* define if fftw3.h exists */
/* #undef HAVE_FFTW3_H */

/* Define to 1 if you have the `z' library (-lz). */
/*#define HAVE_LIBZ 1 */
#define HAVE_LIBZ 0

/* Define to the one symbol short name of this package. */
/* #undef PACKAGE_TARNAME */

/* Define to the version of this package. */
/* #undef PACKAGE_VERSION */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Code compiled in debug mode */
/* #undef debug */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#undef inline
#endif

/* Define to rpl_malloc if the replacement function should be used. */
#undef malloc

/* Define to rpl_realloc if the replacement function should be used. */
#undef realloc

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef size_t

#ifdef SINGLE_PRECISION
typedef float RealType;
#ifdef IS_MPI
#define MPI_REALTYPE MPI_FLOAT
#define MPI_REALTYPE_INT MPI_FLOAT_INT
#endif
#else
typedef double RealType;
#ifdef IS_MPI
#define MPI_REALTYPE MPI_DOUBLE
#define MPI_REALTYPE_INT MPI_DOUBLE_INT
#endif
#endif

#endif // __CONFIG_H
