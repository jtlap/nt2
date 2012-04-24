//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_DETAILS_LAPACK_POTRF_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_DETAILS_LAPACK_POTRF_HPP_INCLUDED

#include <complex>
#include <nt2/toolbox/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(dpotrf)( const char* uplo, const nt2_la_int* n
                          , double* a       , const nt2_la_int* lda
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(spotrf)( const char* uplo, const nt2_la_int* n
                          , float* a        , const nt2_la_int* lda
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(cpotrf)( const char* uplo  , const nt2_la_int* n
                          , nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zpotrf)(const char* uplo   , const nt2_la_int* n
                          , nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace details
{
#define NT2_POTRF(NAME, T)                                \
inline void potrf ( const char* uplo, const nt2_la_int* n   \
                  , T* a            , const nt2_la_int* lda \
                  , nt2_la_int* info                      \
                  )                                       \
{                                                         \
  NT2_F77NAME(NAME)(uplo, n, a, lda, info);               \
}                                                         \
/**/

  NT2_POTRF(spotrf, float)
  NT2_POTRF(dpotrf, double)
  NT2_POTRF(cpotrf, std::complex<float>)
  NT2_POTRF(zpotrf, std::complex<double>)

#undef NT2_POTRF
} }

#endif
