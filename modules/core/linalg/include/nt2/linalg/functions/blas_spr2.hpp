//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_SPR2_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_SPR2_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_spr2 function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_spr2 function tag
    struct blas_spr2_ : ext::abstract_<blas_spr2_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_spr2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_spr2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_spr2_, Site> dispatching_blas_spr2_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_spr2_, Site>();
    }
    template<class... Args>
    struct impl_blas_spr2_;
  }

  /*!
    @brief spr2  -  perform  the  symmetric  rank 2 operation for real entries (same as hpr2 in real cases)

    a += alpha*x*trans(y) + conj(alpha)*y*trans(x)

    @param      uplo   - char
              on  entry,  uplo specifies whether the upper or lower triangular
              part of the array a is to be referenced as follows:

              uplo = 'U' or 'u'   only the upper triangular part of a is to be
              referenced.

              uplo = 'L' or 'l'   only the lower triangular part of a is to be
              referenced.

              unchanged on exit.

     @param alpha  - scalar           .
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

     @param  ap    - container of dimension nxn
             (  (  n*(  n + 1 ) )/2 ).  before entry with  uplo = 'u' or 'u',
              the array ap must contain  the  upper  triangular  part  of  the
              symmetric  matrix packed sequentially, column by column, so that
              ap( 1 ) contains a( 1, 1 ), ap( 2 ) and ap( 3 ) contain a( 1,  2
              )  and  a( 2, 2 ) respectively, and so on. on exit, the array ap
              is overwritten by the  upper  triangular  part  of  the  updated
              matrix.   before entry with uplo = 'l' or 'l', the array ap must
              contain the lower triangular part of the symmetric matrix packed
              sequentially, column by column, so that ap( 1 ) contains a( 1, 1
              ), ap( 2 ) and ap( 3 ) contain a( 2, 1 ) and a( 3, 1  )  respec-
              tively,  and  so on. on exit, the array ap is overwritten by the
              lower triangular part of the  updated  matrix.   note  that  the
              imaginary  parts  of the diagonal elements need not be set, they
              are assumed to be zero, and on exit they are set to zero.
  */

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_spr2_, blas_spr2
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)
                                  , 7
                                  );

}

#endif

