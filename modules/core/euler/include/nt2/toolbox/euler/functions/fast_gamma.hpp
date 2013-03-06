//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_FAST_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_FAST_GAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_fast_gamma fast_gamma
 *
 * \par Description
 * Gamma function
 * \par Formula
 * \f[ \Gamma(a_0)=\int_0^\infty t^{a_0-1}e^{-t}dt\f]The fast prefix indicates less accuracy than gamma
 * function itself and nonguaranted limiting values for the sake of speed.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fast_gamma.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fast_gamma_(A0)>::type
 *     fast_gamma(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_gamma
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
     * \brief Define the tag fast_gamma_ of functor fast_gamma
     *        in namespace nt2::tag for toolbox euler
    **/
    struct fast_gamma_ : ext::elementwise_<fast_gamma_> { typedef ext::elementwise_<fast_gamma_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_gamma_, fast_gamma, 1)
}

#endif

// modified by jt the 25/12/2010
