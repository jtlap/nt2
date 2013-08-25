//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINTS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_toints toints
 *
 * \par Description
 * convert a floating entry to signed integer by truncation.
 * The Inf -Inf and Nan value are treated properly and go to respectively to
 * Valmax, Valmin and Zero of the destination integral type which has the
 * All values superior (resps) less than Valmax (resp Valmin) of the return type
 * are saturated accordingly.
 * same bit size as the entry.
 * On integral typed values the functor acts as identity keeping the entry type.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/toints.hpp>
 * \endcode
 *
 * \par Aliases
 * \arg ifix
 * \arg itrunc
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::toints_(A0)>::type
 *     toints(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of toints
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag toints_ of functor toints
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct toints_ : ext::elementwise_<toints_> { typedef ext::elementwise_<toints_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, toints, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, ifix, 1)
  //  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toints_, itrunc, 1)
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
