//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_TPSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_TPSV_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_tpsv function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_tpsv function tag
    struct blas_tpsv_ : ext::abstract_<blas_tpsv_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_tpsv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_tpsv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_tpsv_, Site> dispatching_blas_tpsv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_tpsv_, Site>();
    }
    template<class... Args>
    struct impl_blas_tpsv_;
  }

  /*!
    @brief tpsv  -  solve  one  of  the systems of equations

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

     @param a  container of triangular array dimension nxn in packed form
              of real size (  (  n*(  n + 1 ) )/2 ).
              before entry with  uplo = 'u' or 'u',
              the array ap must contain the  upper  triangular  matrix  packed
              sequentially, column by column, so that ap( 1 ) contains a( 1, 1
              ), ap( 2 ) and ap( 3 ) contain a( 1, 2 ) and a( 2, 2  )  respec-
              tively,  and  so  on.   before entry with uplo = 'l' or 'l', the
              array ap must contain the lower triangular matrix packed sequen-
              tially,  column  by  column, so that ap( 1 ) contains a( 1, 1 ),
              ap( 2 ) and ap( 3 ) contain a( 2, 1 ) and  a(  3,  1  )  respec-
              tively, and so on.  note that when  diag = 'u' or 'u', the diag-
              onal elements of a are not referenced, but  are  assumed  to  be
              unity.  unchanged on exit.

      @param x  container of dimension at least
              (  1  +  ( n - 1 )*abs( incx ) ).  before entry, the incremented
              array x must contain the n element vector x. on exit, x is over-
              written with the solution vector x.

     @param incx   - integer.
              on  entry,  incx  specifies the increment for the elements of x.
              incx must not be zero.  unchanged on exit.

   **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_tpsv_, blas_tpsv
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(A4&)(const A5&)
                                  , 6
                                  );

}

#endif

