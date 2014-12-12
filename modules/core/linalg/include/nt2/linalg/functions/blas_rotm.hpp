//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_ROTM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_ROTM_HPP_INCLUDED

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
    struct blas_rotm_ : ext::abstract_<blas_rotm_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<blas_rotm_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blas_rotm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::blas_rotm_, Site> dispatching_blas_rotm_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::blas_rotm_, Site>();
    }
    template<class... Args>
    struct impl_blas_rotm_;
  }

  /*!
  @brief Apply plane modified rotation

  @code
  rot( n, x, incx, y, incy, dparam )
  @endcode

  return in overwritten in x and y the result of the first and second line
  of the product :

    [  h11 h12 ] [ x(_(1, incx, (n-1)*incx+1)]
    [  h21 h22 ] [ y(_(1, incy, (n-1)*incy+1)]

    with dparam(1)=dflag, the matrix has one of the following forms..

      dflag=-1.0      dflag=0.0   dflag=1.0     dflag=-2.0

      (h11  dh12)    (1.0  h12)   (h11  1.0)    (1.0  0.0)
    h=(         )    (        )   (        )    (        )
      (h21  dh22),   (h21 1.0 ),  (-1.0 h22),   (0.0  1.0).

    @param n number of elements to take in each vector
    @param x abcissae and L-value to receive rotated  abscissae
    @param incx step through x
    @param y ordinates and L-value to receive rotated ordinates
    @param incy step through y
    @param dparam L-value to receive the result


  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::blas_rotm_, blas_rotm
                                  , (const A0&)(A1&)(const A2&)(A3&)(const A4&)(const A5&)
                                  , 6
                                  );

}

#endif

