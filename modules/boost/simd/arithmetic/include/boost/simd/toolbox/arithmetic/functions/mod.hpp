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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MOD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MOD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_mod mod
 *
 * \par Description
 * The function computes the remainder of dividing a0 by a1.
 * The return value is a0-n*a1, where n is the value a0/a1, rounded to -inf.\par
 * if one prefer: if a1 is zero returns a0, else return
 * a0-divfloor(a0,a1)*a1
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mod.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::mod_(A0,A0)>::type
 *     mod(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of mod
 * \param a1 the second parameter of mod
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag mod_ of functor mod
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct mod_ : ext::elementwise_<mod_> { typedef ext::elementwise_<mod_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mod_, mod, 2)
} }

#endif

// modified by jt the 25/12/2010
