//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_TRSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_TRSV_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_trsv function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_trsv function tag
    struct blas_trsv_ : ext::abstract_<blas_trsv_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_trsv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_trsv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_trsv_, Site> dispatching_blas_trsv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_trsv_, Site>();
    }
    template<class... Args>
    struct impl_blas_trsv_;
  }

  /*!
    @brief trsv  -  solve  one  of  the systems of equations

    mtimes(a, x) = b,
    mtimes(trans(a), x) = b,
    mtimes(ctrans(a), x) = b

   @param uplo   char
              On entry, UPLO specifies whether the matrix is an upper or lower
              triangular matrix as follows:

              uplo = 'U' or 'u'   a is an upper triangular matrix.

              uplo = 'L' or 'l'   a is a lower triangular matrix.

              unchanged on exit.

     @param trans  - char
              On entry, trans specifies the operation to be performed as  follows:

              trans = 'N' or 'n'   x := A*x.

              trans = 'T' or 't'   x := A'*x.

              trans = 'C' or 'c'   x := conjg( A' )*x.

              Unchanged on exit.

     @param diag   - char
              On  entry, diag specifies whether or not A is unit triangular as
              follows:

              diag = 'U' or 'u'   a is assumed to be unit triangular.

              diag = 'N' or 'n'   a is not assumed to be unit triangular.

              unchanged on exit.

      @param a  container of dimension nxn
              before entry with  uplo = 'u' or 'u', the leading n by  n  upper
              triangular part of the array a must contain the upper triangular
              matrix and the strictly lower triangular part of a is not refer-
              enced.   before entry with uplo = 'l' or 'l', the leading n by n
              lower triangular part of the array a must contain the lower tri-
              angular  matrix  and  the strictly upper triangular part of a is
              not referenced.  note that when  diag = 'u' or 'u', the diagonal
              elements  of  a are not referenced either, but are assumed to be
              unity.  unchanged on exit.

     @param x  container of dimension at least
              (  1  +  ( n - 1 )*abs( incx ) ).  before entry, the incremented
              array x must contain the n element vector x. on exit, x is over-
              written with the solution vector x.

     @param incx   - integer.
              on  entry,  incx  specifies the increment for the elements of x.
              incx must not be zero.  unchanged on exit.

   **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_trsv_, blas_trsv
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(A4&)(const A5&)
                                  , 6
                                  );

}

#endif

