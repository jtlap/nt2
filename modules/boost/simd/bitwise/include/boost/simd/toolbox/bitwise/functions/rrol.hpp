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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_RROL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_RROL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_rrol rrol
 *
 * \par Description
 * The function returns the first entry rotated left or right
 * by the absolute value of second entry according to its sign.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rrol.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::rrol_(A0,A0)>::type
 *     rrol(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of rrol
 * \param a1 the second parameter of rrol, must be an integer value
 *
 * \return returns a value of the type of the first parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag rrol_ of functor rrol
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct rrol_ : ext::elementwise_<rrol_> { typedef ext::elementwise_<rrol_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rrol_, rrol, 2)
} }

#endif

// modified by jt the 25/12/2010
