//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_POL2CART_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_POL2CART_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for pol2cart function
    struct pol2cart_ : ext::elementwise_<pol2cart_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<pol2cart_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_pol2cart_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::pol2cart_, Site>
    dispatching_pol2cart_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::pol2cart_, Site>();
    }
    template<class... Args>
    struct impl_pol2cart_;
  }
  /*!
    transforms two-dimensional polar coordinates in Cartesian coordinates

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 rho, theta;
    tie(x, y) = pol2cart(rho, theta);
    @endcode

    is similar to:

    @code
    T0 x =  rho*cos(theta);
    T0 y =  rho*sin(theta);
    @endcode

    @see @funcref{pol2cart}, @funcref{cart2sph}, @funcref{sph2cart}
    @param rho
    @param theta

    @return A Fusion Sequence containing the modulus and angle
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::pol2cart_, pol2cart, 2)

  /*!
    transforms two-dimensional polar coordinates in Cartesian coordinates

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 x, y;
    x= pol2cart(rho, theta, y);
    @endcode

    is similar to:

    @code
    T0 x =  rho*cos(theta);
    T0 y =  rho*sin(theta);
    @endcode

    @param rho
    @param theta
    @param y L-Value that will receive the ordinate

    @return the abscissa
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::pol2cart_, pol2cart
                                  , (A0 const&)(A1 const&)(A2&),3)

  /*!
    transforms two-dimensional polar coordinates in Cartesian coordinates

    For every parameters of floating type T0:

    @par Semantic:

    @code
    T0 x, y;
    pol2cart(rho, theta, x, y);
    @endcode

    is similar to:

    @code
    T0 x =  rho*cos(theta);
    T0 y =  rho*sin(theta);
    @endcode

    @param rho
    @param theta
    @param x L-Value that will receive the abscissa
    @param y L-Value that will receive the ordinate

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::pol2cart_, pol2cart
                                  , (A0 const&)(A1 const&)(A2&)(A3&),4)

    }

#endif


