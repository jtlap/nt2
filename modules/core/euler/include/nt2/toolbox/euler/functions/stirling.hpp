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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_STIRLING_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_STIRLING_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_stirling stirling
 *
 * \par Description
 * Stirling formula for the gamma function
 * \par Formula
 * \f[\Gamma(a_0) \approx \sqrt{2 \pi} a_0^{a_0-\frac12} e^{-a_0} ( 1 + \frac1{a_0} P(\frac1{a_0}))\f]
 * Where P is a polynomial.
 * \parThe formula implementation is usable for a0 between 33 and 172, according cephes
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/stirling.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::stirling_(A0)>::type
 *     stirling(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of stirling
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
     * \brief Define the tag stirling_ of functor stirling
     *        in namespace nt2::tag for toolbox euler
    **/
    struct stirling_ : ext::elementwise_<stirling_> { typedef ext::elementwise_<stirling_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::stirling_, stirling, 1)
}

#endif

// modified by jt the 25/12/2010
