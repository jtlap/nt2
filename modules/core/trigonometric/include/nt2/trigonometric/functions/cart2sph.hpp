//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_CART2SPH_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_CART2SPH_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for cart2sph function
    struct cart2sph_ : ext::elementwise_<cart2sph_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cart2sph_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cart2sph_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::cart2sph_, Site> dispatching_cart2sph_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::cart2sph_, Site>();
    }
    template<class... Args>
    struct impl_cart2sph_;
  }
  /*!
    transforms three-dimensional Cartesian coordinates stored in corresponding elements of arrays x y and z into spherical coordinates.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 az, elev, r;
    tie(az,elev,r) = cart2sph(x, y, z);
    @endcode

    is similar to:

    @code
    T0 r =  sqrt(x*x+y*y+z*z);
    T0 elev =  atan2(z, sqrt(x*x+y*y));
    T0 az =  atan2(y, x);
    @endcode

    @see @funcref{sph2cart}
    @param x
    @param y
    @param z

    @return A Fusion Sequence containing the azimut, elevation and modulus
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::cart2sph_, cart2sph, 3)

  /*!
    transforms three-dimensional Cartesian coordinates stored in corresponding elements of arrays x y and z into spherical coordinates.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 az, elev, r;
    tie(az, elev) = cart2sph(x, y, z, r);
    @endcode

    is similar to:

    @code
    T0 r =  sqrt(x*x+y*y+z*z);
    T0 elev =  atan2(z, sqrt(x*x+y*y));
    T0 az =  atan2(y, x);
    @endcode

    @param x
    @param y
    @param z
    @param r L-Value that will receive the modulus

    @ @return A Fusion Sequence containing the azimut, elevation and modulus
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cart2sph_, cart2sph,(A0 const&)(A1 const&)(A2 const&)(A3&),4)

  /*!
    transforms three-dimensional Cartesian coordinates stored in corresponding elements of arrays x y and z into spherical coordinates.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 az, elev, r;
    az = cart2sph(x, y, z, elev, r);
    @endcode

    is similar to:

    @code
    T0 r =  sqrt(x*x+y*y+z*z);
    T0 elev =  atan2(z, sqrt(x*x+y*y));
    T0 az =  atan2(y, x);
    @endcode

    @param x
    @param y
    @param z
    @param elev L-Value that will receive the elevation
    @param r L-Value that will receive the modulus

    @return the azimut
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cart2sph_, cart2sph,(A0 const&)(A1 const&)(A2 const&)(A3&)(A4&),5)
  /*!
    transforms three-dimensional Cartesian coordinates stored in corresponding elements of arrays x y and z into spherical coordinates.

    For every parameters of floating type T0:

    @par Semantic:

    @code
    T0 az, elev, r;
    cart2sph(x, y, z, az, elev, r);
    @endcode

    is similar to:

    @code
    T0 r =  sqrt(x*x+y*y+z*z);
    T0 elev =  atan2(z, sqrt(x*x+y*y));
    T0 az =  atan2(y, x);
    @endcode

    @param x
    @param y
    @param z
    @param az L-Value that will receive the azimut
    @param elev L-Value that will receive the elevation
    @param r L-Value that will receive the modulus

  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cart2sph_, cart2sph,(A0 const&)(A1 const&)(A2 const&)(A3&)(A4&)(A5&),6)

    }

#endif


