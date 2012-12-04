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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REM_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_rem rem
 *
 * \par Description
 * This function computes the floating-point remainder of dividing a0 by a1.
 * The return value is a0-n*a1, where n is the quotient a0/a1 rounded
 * toward zero to an integer.\par
 * if one prefer: if a1 is zero returns a0, else return
 * a0-divfix(a0,a1)*a1
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rem.hpp>
 * \endcode
 *
 * \par Alias
 * \arg fmod
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::rem_(A0,A0)>::type
 *     rem(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of rem
 * \param a1 the second parameter of rem
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
     * \brief Define the tag rem_ of functor rem
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct rem_ : ext::elementwise_<rem_> { typedef ext::elementwise_<rem_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rem_, rem, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rem_, fmod, 2)
} }

#endif

// modified by jt the 25/12/2010
