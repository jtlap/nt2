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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TWO_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TWO_SPLIT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_two_split two_split
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/two_split.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::two_split_(A0)>::type
 *     two_split(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of two_split
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
     * \brief Define the tag two_split_ of functor two_split
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct two_split_ : ext::elementwise_<two_split_> { typedef ext::elementwise_<two_split_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::two_split_, two_split, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::two_split_, two_split,(A0 const&)(A0&), 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::two_split_, two_split,(A0 const&)(A0&)(A0&), 1)
} }

#endif

// modified by jt the 25/12/2010
