//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_BLAS_ROT_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_BLAS_ROT_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements rot function
**/

#include <nt2/include/functor.hpp>

namespace nt2 { namespace blas
{
  namespace tag
  {
    /// @brief Defines rot function tag
    struct rot_ : ext::abstract_<rot_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<rot_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_rot_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::rot_, Site> dispatching_rot_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::rot_, Site>();
    }
    template<class... Args>
    struct impl_rot_;
  }

  /*!

  @brief Apply plane rotation

  @code
  rot( n, x, incx, y, incy, c, s )
  @endcode

  return in overwritten in x and y the result of the first and second line
  of the product :

    [  c  s ] [ x(_(1, incx, (n-1)*incx+1)]
    [ -s  c ] [ y(_(1, incy, (n-1)*incy+1)]

    @param n number of elements to take in each vector
    @param x abcissae and L-value to receive rotated  abscissae
    @param incx step through x
    @param y ordinates and L-value to receive rotated ordinates
    @param incy step through y
    @param c cosine of the rotation
    @param s sine of the rotation

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::rot_, rot
                                  , (const A0&)(A1&)(const A2&)(A3&)(const A4&)(const A5&)(const A6&)
                                  , 7
                                  );

 } }

#endif

