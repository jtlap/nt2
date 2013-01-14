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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_LO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_LO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_lo lo
 *
 * \par Description
 * The function returns the low part of the entry
 * as an integer of the same size as the input.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lo.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::lo_(A0)>::type
 *     lo(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of lo
 *
 * \return always returns an integer value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag lo_ of functor lo
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct lo_ : ext::elementwise_<lo_> { typedef ext::elementwise_<lo_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lo_, lo, 1)
} }

#endif

// modified by jt the 25/12/2010
