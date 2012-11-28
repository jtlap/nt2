//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/U.B.P.
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ. Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SQR_ABS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_sqr_abs sqr_abs
 *
 * \par Description
 * The function always returns a value of the same type than the entry.
 * \par
 * This is the saturated square modulus of the input.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqr_abs.hpp>
 * \endcode
 *
 * \par Alias
 * \arg sqr_modulus
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sqr_abs_(A0)>::type
 *     sqr_abs(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sqr_abs
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
     * \brief Define the tag sqr_abs_ of functor sqr_abs
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct sqr_abs_ : ext::elementwise_<sqr_abs_> { typedef ext::elementwise_<sqr_abs_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqr_abs_, sqr_abs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqr_abs_, sqr_modulus, 1)
} }

#endif

// modified by jt the 25/12/2010
