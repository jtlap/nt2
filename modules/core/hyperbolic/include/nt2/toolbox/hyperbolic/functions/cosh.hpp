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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_COSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_COSH_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_cosh cosh
 *
 * \par Description
 * hyperbolic cosine: \f$\frac{e^{a_0}+e^{-a_0}}2\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cosh.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::cosh_(A0)>::type
 *     cosh(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cosh
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
     * \brief Define the tag cosh_ of functor cosh
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct cosh_ : ext::elementwise_<cosh_> { typedef ext::elementwise_<cosh_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::cosh_, cosh, 1)
}

#endif

// modified by jt the 25/12/2010
