//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_RSQRT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_rsqrt rsqrt
 *
 * \par Description
 * return a floating point value equal to the inverse
 * of the square root of the entry
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rsqrt.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::rsqrt_(A0)>::type
 *     rsqrt(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of rsqrt
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
     * \brief Define the tag rsqrt_ of functor rsqrt
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct rsqrt_ : ext::elementwise_<rsqrt_> { typedef ext::elementwise_<rsqrt_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rsqrt_, rsqrt, 1)
} }

#endif

// modified by jt the 25/12/2010
