//#include "fdlibm.h"
#ifdef __LITTLE_ENDIAN
#define __lo 0
#define __hi 1
#else
#define __lo 1
#define __hi 0
#endif

typedef union { double d; int ii[2];}  fd_u;

inline int fd___HI(double x)
{
  fd_u u;
  u.d=x;
  return u.ii[__hi];
}

inline int fd___LO(double x)
{
  fd_u u;
  u.d=x;
  return u.ii[__lo];
}

inline void fd__set_LO(double *x, int l)
{
  fd_u u;
  u.d = *x;
  u.ii[__lo]=l;
  *x=u.d;
}

inline void fd__set_HI(double *x, int h)
{
  fd_u u;
  u.d = *x;
  u.ii[__hi]=h;
  *x=u.d;
}
