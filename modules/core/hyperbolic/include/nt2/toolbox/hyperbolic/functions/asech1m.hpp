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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ASECH1M_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ASECH1M_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_asech1m asech1m
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/asech1m.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::asech1m_(A0)>::type
 *     asech1m(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of asech1m
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 {
  namespace tag
  {
    /*!
     * \brief Define the tag asech1m_ of functor asech1m
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct asech1m_ : ext::elementwise_<asech1m_> { typedef ext::elementwise_<asech1m_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::asech1m_, asech1m, 1)
}

#endif
