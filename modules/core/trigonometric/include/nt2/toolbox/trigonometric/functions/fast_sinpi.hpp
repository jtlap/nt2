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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SINPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SINPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_fast_sinpi fast_sinpi
 *
 * \par Description
 * sine of angle in \f$\pi\f$ multiples: \f$\cos(\pi a_0)\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fast_sinpi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fast_sinpi_(A0)>::type
 *     fast_sinpi(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_sinpi
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
     * \brief Define the tag fast_sinpi_ of functor fast_sinpi
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct fast_sinpi_ : ext::elementwise_<fast_sinpi_> { typedef ext::elementwise_<fast_sinpi_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sinpi_, fast_sinpi, 1)
}

#endif

// modified by jt the 25/12/2010
