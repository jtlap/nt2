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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TOFLOAT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_tofloat tofloat
 *
 * \par Description
 * convert an entry to floating points.
 * In SIMD not all integer types can be so converted
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tofloat.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::tofloat_(A0)>::type
 *     tofloat(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of tofloat
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
     * \brief Define the tag tofloat_ of functor tofloat
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct tofloat_ : ext::elementwise_<tofloat_> { typedef ext::elementwise_<tofloat_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tofloat_, tofloat, 1)
} }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
