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
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SINC_PI_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SINC_PI_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/sinc.hpp>

/*!
 * \ingroup boost_math
 * \defgroup boost_math_sinc_pi sinc_pi
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library boost_math.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/boost_math/include/functions/sinc_pi.hpp>
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
 *       meta::call<tag::sinc_pi_(A0)>::type
 *       sinc_pi(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sinc_pi
 *
 * \return a value of the same type as the parameter
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
     * \brief Define the tag sinc_pi_ of functor sinc_pi
     *        in namespace nt2::boost_math::tag for toolbox boost_math
    **/
    struct sinc_pi_ : ext::elementwise_<sinc_pi_> { typedef ext::elementwise_<sinc_pi_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(boost_math::tag::sinc_pi_, sinc_pi, 1)
  } }

#include <nt2/toolbox/boost_math/functions/scalar/sinc_pi.hpp>
// #include <nt2/toolbox/boost_math/functions/simd/all/sinc_pi.hpp>

#endif

// modified by jt the 29/12/2010
