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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_EXP10_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_EXP10_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_exp10 exp10
 *
 * \par Description
 * base ten exponential function: $10^{a_0}$
 * \par
 * provisions are made for otaining a flint result from a flint input
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/exp10.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::exp10_(A0)>::type
 *     exp10(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of exp10
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
     * \brief Define the tag exp10_ of functor exp10
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct exp10_ : ext::elementwise_<exp10_> { typedef ext::elementwise_<exp10_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::exp10_, exp10, 1)
}

#endif

// modified by jt the 25/12/2010
