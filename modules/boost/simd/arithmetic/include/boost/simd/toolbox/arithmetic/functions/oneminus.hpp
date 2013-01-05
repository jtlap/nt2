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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ONEMINUS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ONEMINUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_oneminus oneminus
 *
 * \par Description
 * returns the saturated $1-a_0$ in the input type.
 * Be warned that for unsigned types the result is always 0 or 1!
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/oneminus.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::oneminus_(A0)>::type
 *     oneminus(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of oneminus
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
     * \brief Define the tag oneminus_ of functor oneminus
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct oneminus_ : ext::elementwise_<oneminus_> { typedef ext::elementwise_<oneminus_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::oneminus_, oneminus, 1)
} }

#endif

// modified by jt the 25/12/2010
