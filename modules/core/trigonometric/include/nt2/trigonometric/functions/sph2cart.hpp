//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SPH2CART_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SPH2CART_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for sph2cart function
    struct sph2cart_ : ext::elementwise_<sph2cart_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sph2cart_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_sph2cart_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::sph2cart_, Site>
    dispatching_sph2cart_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::sph2cart_, Site>();
    }
    template<class... Args>
    struct impl_sph2cart_;
  }
  /*!
    transforms three-dimensional spherical coordinates
    in Cartesian coordinates

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 x, y, z;
    tie(x, y, z) = sph2cart(az, elev, r);
    @endcode

    is similar to:

    @code
    T0 x = r*cos(elev)*cos(az);
    T0 y = r*cos(elev)*sin(az);
    T0 z = r*sin(elev);
    @endcode

    @see  @funcref{cart2sph}
    @param az
    @param elev
    @param r

    @return A Fusion Sequence containing the cartesian coordinates
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::sph2cart_, sph2cart, 3)

  /*!
    transforms three-dimensional spherical coordinates
    in Cartesian coordinates

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 x, y, z;
    tie(x, y) = sph2cart(az, elev, r, z);
    @endcode

    is similar to:

    @code
    T0 x = r*cos(elev)*cos(az);
    T0 y = r*cos(elev)*sin(az);
    T0 z = r*sin(elev);
    @endcode

    @see  @funcref{cart2sph}
    @param az
    @param elev
    @param r
    @param z L-Value that will receive the z-coordinate

    @return A Fusion Sequence containing the cartesian coordinates x and y
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sph2cart_, sph2cart
                                  , (A0 const&)(A1 const&)(A2 const&)(A3&),4)

  /*!
    transforms three-dimensional spherical coordinates
    in Cartesian coordinates

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 x, y, z;
    x = sph2cart(az, elev, r, y, z);
    @endcode

    is similar to:

    @code
    T0 x = r*cos(elev)*cos(az);
    T0 y = r*cos(elev)*sin(az);
    T0 z = r*sin(elev);
    @endcode

    @see  @funcref{cart2sph}
    @param az
    @param elev
    @param r
    @param y L-Value that will receive the y-coordinate
    @param z L-Value that will receive the z-coordinate

    @return the x coordinate
  **/

   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sph2cart_, sph2cart
                                  , (A0 const&)(A1 const&)(A2 const &)(A3&)(A4&),5)

  /*!
    transforms three-dimensional spherical coordinates
    in Cartesian coordinates

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 x, y, z;
    sph2cart(az, elev, r, x, y, z);
    @endcode

    is similar to:

    @code
    T0 x = r*cos(elev)*cos(az);
    T0 y = r*cos(elev)*sin(az);
    T0 z = r*sin(elev);
    @endcode

    @see  @funcref{cart2sph}
    @param az
    @param elev
    @param r
    @param x L-Value that will receive the x-coordinate
    @param y L-Value that will receive the y-coordinate
    @param z L-Value that will receive the z-coordinate

  **/

   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sph2cart_, sph2cart
                                  , (A0 const&)(A1 const&)(A2 const &)(A3&)(A4&)(A5&),6)
    }

#endif


