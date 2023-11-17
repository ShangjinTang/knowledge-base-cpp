
#ifndef LIBHELLO_EXPORT_H
#define LIBHELLO_EXPORT_H

#ifdef LIBHELLO_STATIC_DEFINE
#  define LIBHELLO_EXPORT
#  define LIBHELLO_NO_EXPORT
#else
#  ifndef LIBHELLO_EXPORT
#    ifdef libhello_EXPORTS
        /* We are building this library */
#      define LIBHELLO_EXPORT 
#    else
        /* We are using this library */
#      define LIBHELLO_EXPORT 
#    endif
#  endif

#  ifndef LIBHELLO_NO_EXPORT
#    define LIBHELLO_NO_EXPORT 
#  endif
#endif

#ifndef LIBHELLO_DEPRECATED
#  define LIBHELLO_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIBHELLO_DEPRECATED_EXPORT
#  define LIBHELLO_DEPRECATED_EXPORT LIBHELLO_EXPORT LIBHELLO_DEPRECATED
#endif

#ifndef LIBHELLO_DEPRECATED_NO_EXPORT
#  define LIBHELLO_DEPRECATED_NO_EXPORT LIBHELLO_NO_EXPORT LIBHELLO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIBHELLO_NO_DEPRECATED
#    define LIBHELLO_NO_DEPRECATED
#  endif
#endif

#endif /* LIBHELLO_EXPORT_H */
