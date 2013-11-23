#ifndef __PYX_HAVE__fester__integrate
#define __PYX_HAVE__fester__integrate


#ifndef __PYX_HAVE_API__fester__integrate

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

__PYX_EXTERN_C DL_IMPORT(void) print_msg(void);

#endif /* !__PYX_HAVE_API__fester__integrate */

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initintegrate(void);
#else
PyMODINIT_FUNC PyInit_integrate(void);
#endif

#endif /* !__PYX_HAVE__fester__integrate */
