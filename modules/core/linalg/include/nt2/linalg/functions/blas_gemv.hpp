//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_GEMV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_GEMV_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rotm function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines rotm function tag
    struct blas_gemv_ : ext::abstract_<blas_gemv_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_gemv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_gemv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_gemv_, Site> dispatching_blas_gemv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_gemv_, Site>();
    }
    template<class... Args>
    struct impl_blas_gemv_;
  }

  /*!
    @brief gemv  -  perform one of the matrix-vector operations
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

     @param   alpha  real or complex scalar     .
              on  entry, alpha specifies the scalar alpha.  unchanged on exit.

     @param   a mxn container
              before entry, the leading m by n part of the array a  must  con-
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
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_gemv_, blas_gemv
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)(const A7&)
                                  , 8
                                  );

}

#endif

