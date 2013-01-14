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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SAFE_MIN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SAFE_MIN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_safe_min safe_min
 *
 * \par Description
 * Returns the safe_min relative to abs(a0),  ie the minimal
 * value which will not underflow when divided by a0.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/safe_min.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::safe_min_(A0)>::type
 *     safe_min(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of safe_min
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
     * \brief Define the tag safe_min_ of functor safe_min
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct safe_min_ : ext::elementwise_<safe_min_> { typedef ext::elementwise_<safe_min_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::safe_min_, safe_min, 1)
} }

#endif

// modified by jt the 25/12/2010
