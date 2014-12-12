//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_SYR2_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_SYR2_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_syr2 function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_syr2 function tag
    struct blas_syr2_ : ext::abstract_<blas_syr2_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_syr2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_syr2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_syr2_, Site> dispatching_blas_syr2_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_syr2_, Site>();
    }
    template<class... Args>
    struct impl_blas_syr2_;
  }

  /*!
    @brief syr2  -  perform  the  symmetric  rank 2 operation

    a += alpha*x*trans(y) + alpha*y*trans(x)

    @param      uplo   - char
              on  entry,  uplo specifies whether the upper or lower triangular
              part of the array a is to be referenced as follows:

              uplo = 'U' or 'u'   only the upper triangular part of a is to be
              referenced.

              uplo = 'L' or 'l'   only the lower triangular part of a is to be
              referenced.

              unchanged on exit.

     @param alpha  - real or complex scalar accordingly         .
              on  entry, alpha specifies the scalar alpha.  unchanged on exit.

     @param  x container of dimension at least
              ( 1 + ( n - 1 )*abs( incx ) ).  before  entry,  the  incremented
              array x must contain the n element vector x.  unchanged on exit.

     @param  incx   - integer.
              on entry, incx specifies the increment for the  elements  of  x.
              incx must not be zero.  unchanged on exit.

     @param  y  container of dimension at least
              (  1  +  ( n - 1 )*abs( incy ) ).  before entry, the incremented
              array y must contain the n element vector y.  unchanged on exit.

     @param  incy   - integer.
              on  entry,  incy  specifies the increment for the elements of y.
              incy must not be zero.  unchanged on exit.

     @param  a    - container of dimension nxn
              before entry with  uplo = 'u' or 'u', the leading n by  n  upper
              triangular part of the array a must contain the upper triangular
              part of the symmetric matrix and the strictly  lower  triangular
              part  of a is not referenced. on exit, the upper triangular part
              of the array a is overwritten by the upper  triangular  part  of
              the  updated  matrix.   before entry with uplo = 'l' or 'l', the
              leading n by n lower triangular part of the array a must contain
              the  lower  triangular  part  of  the  symmetric  matrix and the
              strictly upper triangular part of a is not referenced. on  exit,
              the  lower  triangular part of the array a is overwritten by the
              lower triangular part of the updated matrix.

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_syr2_, blas_syr2
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)
                                  , 7
                                  );

}

#endif

