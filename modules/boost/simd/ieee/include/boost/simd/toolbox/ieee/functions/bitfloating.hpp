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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_BITFLOATING_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_bitfloating bitfloating
 *
 * \par Description
 * This function is mainly for inner usage and allows
 * speedy writing of \c next, \c nextafter and like functions.
 * \par
 * It transform a pattern of bits stored in an integer value
 * in a floating point with different formulas according to
 * the integer sign (it is the converse of bitinteger)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bitfloating.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitfloating_(A0)>::type
 *     bitfloating(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of bitfloating
 *
 * \return always a floating point value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag bitfloating_ of functor bitfloating
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct bitfloating_ : ext::elementwise_<bitfloating_> { typedef ext::elementwise_<bitfloating_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitfloating_, bitfloating, 1)
} }

#endif

// modified by jt the 25/12/2010
