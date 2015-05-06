//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_CART2POL_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_CART2POL_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
{
    /// @brief Hierarchy tag for cart2pol function
    struct cart2pol_ : ext::elementwise_<cart2pol_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cart2pol_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
        BOOST_AUTO_DECLTYPE_BODY(
          dispatching_cart2pol_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
        };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::cart2pol_, Site>
    dispatching_cart2pol_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::cart2pol_, Site>();
    }
    template<class... Args>
    struct impl_cart2pol_;
  }
  /*!
    transforms two-dimensional Cartesian coordinates stored in corresponding
    elements of arrays x and y into polar coordinates.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 rho, theta;
    tie(rho, theta) = cart2pol(x, y);
    @endcode

    is similar to:

    @code
    T0 rho =  hypot(x, y);
    T0 theta =  atan2(y, x);
    @endcode

    @see @funcref{pol2cart}, @funcref{cart2sph}, @funcref{sph2cart}
    @param x
    @param y

    @return A Fusion Sequence containing the modulus and angle
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::cart2pol_, cart2pol, 2)

  /*!
    transforms two-dimensional Cartesian coordinates stored in corresponding
    elements of arrays x and y into polar coordinates.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 rho, theta;
    rho = cart2pol(x, y, theta);
    @endcode

    is similar to:

    @code
    T0 rho =  hypot(x, y);
    T0 theta =  atan2(y, x);
    @endcode

    @param x
    @param y
    @param rho L-Value that will receive the modulus

    @return the argument
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cart2pol_, cart2pol
                                  , (A0 const&)(A1 const&)(A2&),3)

  /*!
    transforms two-dimensional Cartesian coordinates stored in corresponding
    elements of arrays x and y into polar coordinates.

    For every parameters of floating type T0:

    @par Semantic:

    @code
    T0 rho, theta;
    cart2pol(x, y, rho, theta);
    @endcode

    is similar to:

    @code
    T0 rho =  hypot(x, y);
    T0 theta =  atan2(y, x);
    @endcode

    @param x
    @param y
    @param rho L-Value that will receive the modulus
    @param theta L-Value that will receive the angle

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cart2pol_, cart2pol
                                  , (A0 const&)(A1 const&)(A2&)(A3&),4)

    }

#endif


