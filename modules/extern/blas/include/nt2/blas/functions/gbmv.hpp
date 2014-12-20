//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_GBMV_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_GBMV_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rotm function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines rotm function tag
    struct gbmv_ : ext::abstract_<gbmv_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<gbmv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_gbmv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::gbmv_, Site> dispatching_gbmv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::gbmv_, Site>();
    }
    template<class... Args>
    struct impl_gbmv_;
  }

  /*!
    @brief gbmv  -  perform one of the matrix-vector operations
    y := alpha*a*x +  beta*y,
    or
    y := alpha*a'*x + beta*y,
    or
    y := alpha*conj(a')*x + beta*y

    where  alpha and beta are scalars, x and y are vectors and A is an m by
    n matrix.
    ' denotes (conjugate) transposition and  * matrix vector product



    @param   trans  - character*1.
             on entry, trans specifies the operation to be performed as  follows:

             trans = 'N' or 'n'   y := alpha*a*x + beta*y.

             trans = 'T' or 't'   y := alpha*a'*x + beta*y.

             trans = 'C' or 'c'   y := alpha*conj( a' )*x + beta*y.

             unchanged on exit.

     @param m number of rows of a

     @param kl  on entry, kl specifies the number of sub-diagonals of the matrix
              a. kl must satisfy  0 .le. kl >= 0.  unchanged on exit.

     @param kl  on entry, kl specifies the number of super-diagonals of the matrix
              a. ku must satisfy  0 .le. ku >= 0.  unchanged on exit.

     @param   alpha  real or complex scalar     .
              on  entry, alpha specifies the scalar alpha.  unchanged on exit.

     @param   a mxn container stored a kl,  ku band in a (kl+ku+1)xn array
              before entry, the leading (kl+ku+1)xm by n part of the array a  must  con-
              tain the matrix of coefficients.  unchanged on exit.

      @param  x container of dimension at least
              (  1  +  (  n - 1 )*abs( incx ) ) when trans = 'n' or 'n' and at
              least ( 1 + ( m - 1 )*abs( incx ) )  otherwise.   before  entry,
              the incremented array x must contain the vector x.  unchanged on
              exit.

      @param  incx   - integer.
              on entry, incx specifies the increment for the  elements  of  x.
              incx must not be zero.  unchanged on exit.

      @param  beta    real or complex scalar     .
              on  entry, beta specifies the scalar beta. when beta is supplied
              as zero then y need not be set on input.  unchanged on exit.

      @param  y   L-value container of dimension at least
              ( 1 + ( m - 1 )*abs( incy ) ) when trans = 'n'  or  'n'  and  at
              least  (  1  +  ( n - 1 )*abs( incy ) ) otherwise.  before entry
              with beta non-zero, the incremented array  y  must  contain  the
              vector y. on exit, y is overwritten by the updated vector y.

      @param  incy   - integer.
              on  entry,  incy  specifies the increment for the elements of y.
              incy must not be zero.  unchanged on exit.

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::gbmv_, gbmv
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(const A6&)(const A7&)(A8&)(const A9&)
                                  , 10
                                  );
  // T M KL KU ALPHA A X INCX Y INCY
 } }

#endif

