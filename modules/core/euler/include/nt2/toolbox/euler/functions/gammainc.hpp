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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_GAMMAINC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_GAMMAINC_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_gammainc gammainc
 *
 * \par Description
 * Incomplete Gamma function
 * \par Formula
 * \f[ gammainc(x)=\int_0^\a t^{x-1}e^{-t}dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/gammainc.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::gammainc_(A0, A1)>::type
 *     gammainc(const A0 & x, const A0& a);
 * }
 * \endcode
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag gammainc_ of functor gammainc
     *        in namespace nt2::tag for toolbox euler
    **/
    struct gammainc_ : ext::elementwise_<gammainc_> { typedef ext::elementwise_<gammainc_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::gammainc_, gammainc, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::gammainc_, gammainc, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::gammainc_, gammainc, 4)
}

#endif

// modified by jt the 25/12/2010
