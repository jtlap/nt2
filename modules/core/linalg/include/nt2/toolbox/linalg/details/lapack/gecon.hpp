/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_DETAILS_LAPACK_GECON_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_DETAILS_LAPACK_GECON_HPP_INCLUDED
#include <nt2/toolbox/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>

namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgecon)(const char* norm, const nt2_la_int* n, const nt2_la_complex* a,
                           const nt2_la_int* lda, const float* anorm, float* rcond,
                           nt2_la_complex* work, float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgecon)(const char* norm, const nt2_la_int* n, const double* a,
                           const nt2_la_int* lda, const double* anorm, double* rcond,
                           double* work, nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(sgecon)(const char* norm, const nt2_la_int* n, const float* a,
                           const nt2_la_int* lda, const float* anorm, float* rcond,
                           float* work, nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(zgecon)(const char* norm, const nt2_la_int* n, const nt2_la_complex* a,
                           const nt2_la_int* lda, const double* anorm, double* rcond,
                           nt2_la_complex* work, double* rwork, nt2_la_int* info);
    }
     
#define NT2_GECON(NAME, T)                      \
    inline void gecon(const char* norm,         \
                      const nt2_la_int* n,      \
                      const T* a,               \
                      const nt2_la_int* lda,    \
                      const T* anorm,           \
                      T* rcond,                 \
                      nt2_la_int* info,         \
                      workspace<T> & w)         \
    {                                           \
      w.resize_integers(*n);                           \
      w.resize_main(4**n);                          \
      NT2_F77NAME( NAME )(norm, n, a, lda, anorm,                   \
                          rcond, w.main(), w.integers(), info);        \
    }                                                               \
    inline void gecon(const char* norm,                             \
                      const nt2_la_int* n,                          \
                      const T* a,                                   \
                      const nt2_la_int* lda,                        \
                      const T* anorm,                               \
                      T* rcond,                                     \
                      nt2_la_int* info)                             \
    {                                                               \
      workspace<T> w;                                               \
      gecon(norm, n, a, lda, anorm, rcond, info, w);                \
    }                                                               \
        
    NT2_GECON(sgecon, float)
    NT2_GECON(dgecon, double)
      
#undef NT2_GECON
#define NT2_GECON(NAME, T, TBASE)               \
    inline void gecon(const char* norm,         \
                      const nt2_la_int* n,      \
                      const T* a,               \
                      const nt2_la_int* lda,    \
                      const TBASE* anorm,       \
                      TBASE* rcond,             \
                      nt2_la_int* info,         \
                      workspace<T> & w)         \
    {                                           \
      w.resize_reals(2**n);                     \
      w.resize_main(2**n);                      \
      NT2_F77NAME( NAME )(norm, n, a, lda, anorm,                   \
                          rcond, w.main(), w.reals(), info);        \
    }                                                               \
    inline void gecon(const char* norm,                             \
                      const nt2_la_int* n,                          \
                      const T* a,                                   \
                      const nt2_la_int* lda,                        \
                      const TBASE* anorm,                           \
                      TBASE* rcond,                                 \
                      nt2_la_int* info)                             \
    {                                                               \
      workspace<T> w;                                               \
      gecon(norm, n, a, lda, anorm, rcond, info, w);                \
    }                                                               \
        
    NT2_GECON(cgecon, std::complex<float>, float)
    NT2_GECON(zgecon, std::complex<double>, double)
      
#undef NT2_GECON
      }
}
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of gecon.hpp
// /////////////////////////////////////////////////////////////////////////////
