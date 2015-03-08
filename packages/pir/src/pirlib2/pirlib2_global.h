#ifndef PIRLIB2_GLOBAL_H
#define PIRLIB2_GLOBAL_H


#ifdef WIN32
    #ifndef PIRLIB2_STATIC
        #define DECL_EXPORT __declspec(dllexport)
        #define DECL_IMPORT __declspec(dllimport)
    #else
        #define DECL_EXPORT
        #define DECL_IMPORT
    #endif
#else
    #define DECL_EXPORT
    #define DECL_IMPORT
#endif

#if defined(PIRLIB2_LIBRARY)
#  define PIRLIB2SHARED_EXPORT DECL_EXPORT
#else
#  define PIRLIB2SHARED_EXPORT DECL_IMPORT
#endif


#endif // PIRLIB2_GLOBAL_H
