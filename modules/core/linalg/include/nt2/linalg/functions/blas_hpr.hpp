//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_HPR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_HPR_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_hpr function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_hpr function tag
    struct blas_hpr_ : ext::abstract_<blas_hpr_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_hpr_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_hpr_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_hpr_, Site> dispatching_blas_hpr_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_hpr_, Site>();
    }
    template<class... Args>
    struct impl_blas_hpr_;
  }

  /*!
    @brief hpr   performs the hermitian rank 1 operation with packed matrix

          a += alpha*x*ctrans(x)

       whpre alpha is a real scalar, x is an n element vector and a is an n by
       n symmetric matrix.

      uplo   - char
              on entry, uplo specifies whethpr the upper or  lower  triangular
              part of the array a is to be referenced as follows:

              uplo = 'U' or 'u'   only the upper triangular part of a is to be
              referenced.

              uplo = 'L' or 'l'   only the lower triangular part of a is to be
              referenced.

              unchanged on exit.

        alpha  - real scalar            .
              on entry, alpha specifies the scalar alpha.  unchanged on  exit.

       x      container of dimension at least
              (  1  +  ( n - 1 )*abs( incx ) ).  before entry, the incremented
              array x must contain the n element vector x.  unchanged on exit.

       incx   - integer.
              on  entry,  incx  specifies the increment for the elements of x.
              incx must not be zero.  unchanged on exit.

       a      container of dimension nxn in packed form.
              ( ( n*( n + 1 ) )/2 ).  Before entry with  uplo =  'U'  or  'u',
              the  array a must contain the upper triangular part of the her-
              mitian matrix packed sequentially, column by column, so that ap(
              1  )  contains  a( 1, 1 ), ap( 2 ) and ap( 3 ) contain a( 1, 2 )
              and a( 2, 2 ) respectively, and so on. on exit, the array ap  is
              overwritten  by the upper triangular part of the updated matrix.
              before entry with uplo = 'L' or 'l', the array ap  must  contain
              the  lower  triangular  part  of  the  hermitian  matrix  packed
              sequentially, column by column, so that ap( 1 ) contains a( 1, 1
              ),  ap(  2 ) and ap( 3 ) contain a( 2, 1 ) and a( 3, 1 ) respec-
              tively, and so on. on exit, the array ap is overwritten  by  the
              lower  triangular  part  of  the  updated matrix.  note that the
              imaginary parts of the diagonal elements need not be  set,  they
              are assumed to be zero, and on exit they are set to zero.

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_hpr_, blas_hpr
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(A4&)
                                  , 5
                                  );

}

#endif

