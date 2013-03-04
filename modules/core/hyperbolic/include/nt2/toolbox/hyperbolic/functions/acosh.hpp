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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ACOSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ACOSH_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_acosh acosh
 *
 * \par Description
 * hyperbolic cosine argument: \f$\log(a_0+\sqrt{a_0^2-1})\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/acosh.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::acosh_(A0)>::type
 *     acosh(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of acosh
 *
 * \return nan for a0 less than one
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag acosh_ of functor acosh
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct acosh_ : ext::elementwise_<acosh_> { typedef ext::elementwise_<acosh_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::acosh_, acosh, 1)
}

#endif

// modified by jt the 25/12/2010
