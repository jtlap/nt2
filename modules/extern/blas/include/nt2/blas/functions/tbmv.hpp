//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_TBMV_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_TBMV_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements tbmv function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines tbmv function tag
    struct tbmv_ : ext::abstract_<tbmv_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<tbmv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_tbmv_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::tbmv_, Site> dispatching_tbmv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::tbmv_, Site>();
    }
    template<class... Args>
    struct impl_tbmv_;
  }

  /*!
    @brief tbmv  -  perform  one  of the matrix-vector operations
    x = mtimes(a, x)
    x = mtimes(trans(a), x)
    x = mtimes(ctrans(a), x)

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
              stored in array of DIMENSION ( k+1, n ).
              representing a triangular nxn matrix in band format
              Before entry with UPLO = 'U' or 'u', the leading ( k + 1 ) by  n
              part  of the array A must contain the upper triangular band part
              of the matrix of coefficients, supplied column by  column,  with
              the  leading  diagonal  of  the  matrix  in row ( k + 1 ) of the
              array, the first super-diagonal starting at position 2 in row k,
              and  so  on.  The top left k by k triangle of the array A is not
              referenced.  The following  program  segment  will  transfer  an
              upper triangular band matrix from conventional full matrix stor-
              age to band storage:

              Before  entry with UPLO = 'L' or 'l', the leading ( k + 1 ) by n
              part of the array A must contain the lower triangular band  part
              of  the  matrix of coefficients, supplied column by column, with
              the leading diagonal of the matrix in row 1 of  the  array,  the
              first  sub-diagonal  starting at position 1 in row 2, and so on.
              The bottom right k by k triangle of the array A  is  not  refer-
              enced.  The following program segment will transfer a lower tri-
              angular band matrix from conventional  full  matrix  storage  to
              band storage:

      @param x  container of dimension at least
              (  1  +  ( n - 1 )*abs( incx ) ).  before entry, the incremented
              array x must contain the n element vector x. on exit, x is over-
              written with the tranformed vector x.

       @param incx   - integer.
              on  entry,  incx  specifies the increment for the elements of x.
              incx must not be zero.  unchanged on exit.
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::tbmv_, tbmv
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(A4&)(const A5&)
                                  , 6
                                  );

 } }

#endif

