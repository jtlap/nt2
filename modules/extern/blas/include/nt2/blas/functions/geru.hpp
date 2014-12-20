//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_GERU_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_GERU_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements geru function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines geru function tag
    struct geru_ : ext::abstract_<geru_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<geru_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_geru_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::geru_, Site> dispatching_geru_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::geru_, Site>();
    }
    template<class... Args>
    struct impl_geru_;
  }

  /*!
    @brief geru - perform the rank 1 operation   a += alpha*x*trans(y)

    @param  alpha  real or complex scalar accordingly
              on  entry, alpha specifies the scalar alpha.  unchanged on exit.

    @param x  container of dimension at least
              (  1  +  ( m - 1 )*abs( incx ) ).  before entry, the incremented
              array x must contain the m element vector x.  unchanged on exit.

    @param incx   - integer.
              on  entry,  incx  specifies the increment for the elements of x.
              incx must not be zero.  unchanged on exit.

    @param y  container of dimension at least
              ( 1 + ( n - 1 )*abs( incy ) ).  before  entry,  the  incremented
              array y must contain the n element vector y.  unchanged on exit.

    @param incy   - integer.
              on entry, incy specifies the increment for the  elements  of  y.
              incy must not be zero.  unchanged on exit.

    @param a   container of dimension mxn.
              before  entry,  the leading m by n part of the array a must con-
              tain the matrix of coefficients. on exit, a  is  overwritten  by
              the updated matrix.
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::geru_, geru
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(A5&)
                                  , 6
                                  );

 } }

#endif

