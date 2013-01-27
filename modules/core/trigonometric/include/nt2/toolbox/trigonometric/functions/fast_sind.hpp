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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SIND_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SIND_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_fast_sind fast_sind
 *
 * \par Description
 * sine of the angle in degree, in the interval \f$[-45, 45]\f$, nan outside.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fast_sind.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fast_sind_(A0)>::type
 *     fast_sind(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_sind
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
     * \brief Define the tag fast_sind_ of functor fast_sind
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct fast_sind_ : ext::elementwise_<fast_sind_> { typedef ext::elementwise_<fast_sind_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sind_, fast_sind, 1)
}

#endif

// modified by jt the 25/12/2010
