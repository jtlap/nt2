//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SPH_BESSEL_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SPH_BESSEL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/bessel.hpp>

/*!
 * \ingroup boost_math
 * \defgroup boost_math_sph_bessel sph_bessel
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library boost_math.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/boost_math/include/functions/sph_bessel.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace boost_math
 *   {
 *     template <class A0>
 *       meta::call<tag::sph_bessel_(A0,A0)>::type
 *       sph_bessel(const A0 & a0,const A0 & a1);
 *   }
 * }
 * \endcode
 *
 * \param a0 the first parameter of sph_bessel
 * \param a1 the second parameter of sph_bessel
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * When calling external library, nt2 simply encapsulates the
 * original proper call to provide easy use.
 * \par
 * Remenber that SIMD implementation is therefore merely
 * mapping the scalar function to each SIMD vectors elements
 * and will not provide acceleration, but ease.
 *
**/

namespace nt2 { namespace boost_math { namespace tag
  {
    /*!
     * \brief Define the tag sph_bessel_ of functor sph_bessel
     *        in namespace nt2::boost_math::tag for toolbox boost_math
    **/
    struct sph_bessel_ : ext::elementwise_<sph_bessel_> { typedef ext::elementwise_<sph_bessel_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(boost_math::tag::sph_bessel_, sph_bessel, 2)
  } }

#include <nt2/toolbox/boost_math/functions/scalar/sph_bessel.hpp>
// #include <nt2/toolbox/boost_math/functions/simd/all/sph_bessel.hpp>

#endif

// modified by jt the 29/12/2010
