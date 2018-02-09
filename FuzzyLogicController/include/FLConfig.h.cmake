#ifndef FLConfig_h
#define FLConfig_h

// Library is either compiled static or shared
// Used to set declspec(import, export) in headers if required under Windows
#cmakedefine BUILD_SHARED_LIBS

// Under Windows, for shared libraries (DLL) we need to define export on
// compilation or import on use (like a third party project).
// We exploit here the fact that cmake auto set xxx_EXPORTS (with S) on 
// compilation.
#if defined (WIN32) && defined(BUILD_SHARED_LIBS)
#  ifdef us_elas_EXPORTS
#    define FL_EXPORT __declspec(dllexport)
#  else
#    define FL_EXPORT __declspec(dllimport)
#  endif
#else
#  define FL_EXPORT
#endif

#endif


