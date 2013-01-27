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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_COSD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_COSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_fast_cosd fast_cosd
 *
 * \par Description
 * cosine of the angle in degree, in the interval \f$[-45, 45]\f$, nan outside.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fast_cosd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fast_cosd_(A0)>::type
 *     fast_cosd(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_cosd
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag fast_cosd_ of functor fast_cosd
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct fast_cosd_ : ext::elementwise_<fast_cosd_> { typedef ext::elementwise_<fast_cosd_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cosd_, fast_cosd, 1)
}

#endif

// modified by jt the 25/12/2010
