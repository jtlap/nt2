/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_DETAILS_LAPACK_GESVX_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_DETAILS_LAPACK_GESVX_HPP_INCLUDED
#include <nt2/toolbox/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const float* r, const float* c, nt2_la_complex* b, const nt2_la_int* ldb,
                               nt2_la_complex* x, const nt2_la_int* ldx, float* rcond, float* ferr, float* berr, nt2_la_complex* work,
                               float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const double* a, const nt2_la_int* lda, double* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const double* r, const double* c, double* b, const nt2_la_int* ldb,
                               double* x, const nt2_la_int* ldx, double* rcond, double* ferr, double* berr, double* work,
                               nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(sgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const float* a, const nt2_la_int* lda, float* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const float* r, const float* c, float* b, const nt2_la_int* ldb,
                               float* x, const nt2_la_int* ldx, float* rcond, float* ferr, float* berr, float* work,
                               nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(zgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const double* r, const double* c, nt2_la_complex* b, const nt2_la_int* ldb,
                               nt2_la_complex* x, const nt2_la_int* ldx, double* rcond, double* ferr, double* berr, nt2_la_complex* work,
                               double* rwork, nt2_la_int* info);
    }
    
#define NT2_GESVX(NAME, T, TBASE)                                       \
    inline void gesvx(const char* fact,                                 \
                      const char* trans,                                \
                      const nt2_la_int* n,                              \
                      const nt2_la_int* nrhs,                           \
                      const T* a,                                       \
                      const nt2_la_int* lda,                            \
                      T* af,                                            \
                      const nt2_la_int* ldaf,                           \
                      nt2_la_int* ipiv,                                 \
                      char* equed,                                      \
                      const TBASE* r,                                   \
                      const TBASE* c,                                   \
                      T* b,                                             \
                      const nt2_la_int* ldb,                            \
                      T* x,                                             \
                      const nt2_la_int* ldx,                            \
                      TBASE* rcond,                                     \
                      TBASE* ferr,                                      \
                      TBASE* berr,                                      \
                      nt2_la_int* info,                                 \
                      workspace<T> & w)                                 \
    {                                                                   \
      w.resize_reals(2**n);                                             \
      w.resize_main(2**n);                                              \
      NT2_F77NAME( NAME )(fact, trans, n, nrhs, a, lda, af, ldaf,       \
                          ipiv, equed, r, c, b, ldb, x, ldx,            \
                          rcond, ferr, berr, w.main(),                  \
                          w.reals(), info);                             \
    }                                                                   \
    inline void gesvx(const char* fact,                                 \
                      const char* trans,                                \
                      const nt2_la_int* n,                              \
                      const nt2_la_int* nrhs,                           \
                      const T* a,                                       \
                      const nt2_la_int* lda,                            \
                      T* af,                                            \
                      const nt2_la_int* ldaf,                           \
                      nt2_la_int* ipiv,                                 \
                      char* equed,                                      \
                      const TBASE* r,                                   \
                      const TBASE* c,                                   \
                      T* b,                                             \
                      const nt2_la_int* ldb,                            \
                      T* x,                                             \
                      const nt2_la_int* ldx,                            \
                      TBASE* rcond,                                     \
                      TBASE* ferr,                                      \
                      TBASE* berr,                                      \
                      nt2_la_int* info)                                 \
    {                                                                   \
      workspace<T> w;                                                   \
      gesvx(fact, trans, n, nrhs, a, lda, af, ldaf, ipiv,               \
            equed, r, c, b, ldb, x, ldx,                                \
            rcond, ferr, berr, info, w);                                \
    }                                                                   \
        
    NT2_GESVX(cgesvx, float,  float)
    NT2_GESVX(zgesvx, double, double)
    NT2_GESVX(cgesvx, std::complex<float>,  float)
    NT2_GESVX(zgesvx, std::complex<double>, double)
      
#undef NT2_GESVX
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of svx.hpp
// /////////////////////////////////////////////////////////////////////////////
