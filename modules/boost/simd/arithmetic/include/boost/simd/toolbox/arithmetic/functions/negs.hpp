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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_NEGS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_NEGS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_negs negs
 *
 * \par Description
 * returns saturation of $-a_0$ in the input type.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/negs.hpp>
 * \endcode
 *
 * \par Alias
 * \arg saturated_neg
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::negs_(A0)>::type
 *     negs(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of negs
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd {
  namespace tag
  {
    /*!
     * \brief Define the tag negs_ of functor negs
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct negs_ : ext::elementwise_<negs_> { typedef ext::elementwise_<negs_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negs_, negs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negs_, saturated_neg, 1)
} }

#endif
