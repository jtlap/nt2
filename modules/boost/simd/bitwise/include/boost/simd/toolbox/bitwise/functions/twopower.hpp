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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_TWOPOWER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_TWOPOWER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_twopower twopower
 *
 * \par Description
 * The function returns greatest power of two less or equal to the input.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/twopower.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::twopower_(A0)>::type
 *     twopower(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of twopower
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
     * \brief Define the tag twopower_ of functor twopower
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct twopower_ : ext::elementwise_<twopower_> { typedef ext::elementwise_<twopower_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::twopower_, twopower, 1)
} }

#endif

// modified by jt the 25/12/2010
