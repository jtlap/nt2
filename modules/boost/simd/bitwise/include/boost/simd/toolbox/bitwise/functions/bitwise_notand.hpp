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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_NOTAND_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_bitwise_notand bitwise_notand
 *
 * \par Description
 * return the bitwise and of the bitwise complement of the first parameter with the second parameter.\par
 * The operands must share the same bit size and
 * the result type is the one of the first operand
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bitwise_notand.hpp>
 * \endcode
 *
 * \par Alias
 * \arg b_notand
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::bitwise_notand_(A0,A1)>::type
 *     bitwise_notand(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of bitwise_notand
 * \param a1 the second parameter of bitwise_notand
 *
 * \return a value of the type of the first parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag bitwise_notand_ of functor bitwise_notand
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct bitwise_notand_ : ext::elementwise_<bitwise_notand_> { typedef ext::elementwise_<bitwise_notand_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_notand_, bitwise_notand, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_notand_, b_notand, 2)
} }

#endif

// modified by jt the 25/12/2010
