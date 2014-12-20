//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_SYR_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_SYR_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements syr function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines syr function tag
    struct syr_ : ext::abstract_<syr_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<syr_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_syr_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::syr_, Site> dispatching_syr_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::syr_, Site>();
    }
    template<class... Args>
    struct impl_syr_;
  }

  /*!
    @brief syr   performs the symmetric rank 1 operation

          a += alpha*x*trans(x)

       where alpha is a scalar, x is an n element vector and a is an n by
       n symmetric matrix.

      uplo   - char
              on entry, uplo specifies whether the upper or  lower  triangular
              part of the array a is to be referenced as follows:

              uplo = 'U' or 'u'   only the upper triangular part of a is to be
              referenced.

              uplo = 'L' or 'l'   only the lower triangular part of a is to be
              referenced.

              unchanged on exit.

        ALPHA  - scalar            .
              On entry, ALPHA specifies the scalar alpha.  Unchanged on  exit.

       X      container of dimension at least
              (  1  +  ( n - 1 )*abs( INCX ) ).  Before entry, the incremented
              array X must contain the n element vector x.  Unchanged on exit.

       INCX   - INTEGER.
              On  entry,  INCX  specifies the increment for the elements of X.
              INCX must not be zero.  Unchanged on exit.

       A      container of dimension nxn.
              Before entry with  UPLO = 'U' or 'u', the leading n by  n  upper
              triangular part of the array A must contain the upper triangular
              part of the symmetric matrix and the strictly  lower  triangular
              part  of A is not referenced. On exit, the upper triangular part
              of the array A is overwritten by the upper  triangular  part  of
              the  updated  matrix.   Before entry with UPLO = 'L' or 'l', the
              leading n by n lower triangular part of the array A must contain
              the  lower  triangular  part  of  the  symmetric  matrix and the
              strictly upper triangular part of A is not referenced. On  exit,
              the  lower  triangular part of the array A is overwritten by the
              lower triangular part of the updated matrix.
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::syr_, syr
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(A4&)
                                  , 5
                                  );

 } }

#endif

