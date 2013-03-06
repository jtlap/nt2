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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SQR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SQR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_sqr sqr
 *
 * \par Description
 * return the square of the entry
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqr.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sqr_(A0)>::type
 *     sqr(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sqr
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
     * \brief Define the tag sqr_ of functor sqr
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct sqr_ : ext::elementwise_<sqr_> { typedef ext::elementwise_<sqr_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqr_, sqr, 1)
} }

#endif

// modified by jt the 25/12/2010
