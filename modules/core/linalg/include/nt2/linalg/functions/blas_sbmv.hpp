//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_SBMV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_SBMV_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements blas_sbmv function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines blas_sbmv function tag
    struct blas_sbmv_ : ext::abstract_<blas_sbmv_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_sbmv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_sbmv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_sbmv_, Site> dispatching_blas_sbmv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_sbmv_, Site>();
    }
    template<class... Args>
    struct impl_blas_sbmv_;
  }

  /*!
    @brief      sbmv  performs  the  matrix-vector  operation y = alpha*ab*x + beta*y,
       where alpha and beta are scalars, x and y are n element vectors  and  ab
       is an n by n BAND symmetric matrix. (not defined for complex entries)

    @param      uplo   - char
              on  entry,  uplo specifies whether the upper or lower triangular
              part of the array a is to be referenced as follows:

              uplo = 'U' or 'u'   the upper triangular part of a  is  supplied
              in ap.

              uplo = 'L' or 'l'  The lower triangular part of a is supplied
              in ap.

              unchanged on exit.

     @param  alpha  real scalar
              on  entry, alpha specifies the scalar alpha.  unchanged on exit.

     @param  ab   -  symmetric container of dimension nxn in packed form
              before entry with uplo = 'u' or 'u', the leading ( k + 1 ) by  n
              part  of the array a must contain the upper triangular band part
              of the symmetric matrix, supplied column  by  column,  with  the
              leading  diagonal  of  the matrix in row ( k + 1 ) of the array,
              the first super-diagonal starting at position 2 in row k, and so
              on.  the  top  left k by k triangle of the array a is not refer-
              enced.

              before  entry with uplo = 'l' or 'l', the leading ( k + 1 ) by n
              part of the array a must contain the lower triangular band  part
              of  the  symmetric  matrix,  supplied column by column, with the
              leading diagonal of the matrix in row 1 of the array, the  first
              sub-diagonal  starting  at  position  1 in row 2, and so on. the
              bottom right k by k triangle of the array a is  not  referenced.

     @param  x container of dimension at least
             (  1  +  ( n - 1 )*abs( incx ) ).  before entry, the incremented
              array x must contain the n-  element  vector  x.   unchanged  on
              exit.

     @param incx   - integer
              on  entry,  incx  specifies the increment for the elements of x.
              incx must not be zero.  unchanged on exit.

     @param  beta   real  scalar
              on entry, beta specifies the scalar beta. when beta is  supplied
              as zero then y need not be set on input.  unchanged on exit.

     @param  y container of dimension at least
              (  1  +  ( n - 1 )*abs( incy ) ).  before entry, the incremented
              array y must contain the n element vector y. on exit, y is over-
              written by the updated vector y.

     @param incy   - integer
              on  entry,  incy  specifies the increment for the elements of y.
              incy must not be zero.  unchanged on exit.

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_sbmv_, blas_sbmv
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(const A5&)(A6&)(const A7&)
                                  , 8
                                  );

}

#endif

