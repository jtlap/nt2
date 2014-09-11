//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_POTRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_POTRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

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

#endif
