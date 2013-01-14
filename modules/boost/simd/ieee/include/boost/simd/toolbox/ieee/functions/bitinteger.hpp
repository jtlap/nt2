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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_BITINTEGER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_BITINTEGER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_bitinteger bitinteger
 *
 * \par Description
 * This function is mainly for inner usage and allows
 * speedy writing of \c next, \c nextafter and like functions
 * \par
 * It transforms a floating point value in a pattern of bits
 * stored in an integer with different formulas according to
 * the floating point sign (it is the converse of bitfloating)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bitinteger.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitinteger_(A0)>::type
 *     bitinteger(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of bitinteger
 *
 * \return always an integer value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag bitinteger_ of functor bitinteger
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct bitinteger_ : ext::elementwise_<bitinteger_> { typedef ext::elementwise_<bitinteger_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitinteger_, bitinteger, 1)
} }

#endif

// modified by jt the 25/12/2010
