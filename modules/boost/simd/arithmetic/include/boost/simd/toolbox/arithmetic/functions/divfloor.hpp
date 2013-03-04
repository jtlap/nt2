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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVFLOOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_divfloor divfloor
 *
 * \par Description
 * return the \c floor of the operands real divisionin the input type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/divfloor.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::divfloor_(A0,A0)>::type
 *     divfloor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of divfloor
 * \param a1 the second parameter of divfloor
 *
 * \return a value of the common type of the parameters
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
     * \brief Define the tag divfloor_ of functor divfloor
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct divfloor_ : ext::elementwise_<divfloor_> { typedef ext::elementwise_<divfloor_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divfloor_, divfloor, 2)
} }

#endif
