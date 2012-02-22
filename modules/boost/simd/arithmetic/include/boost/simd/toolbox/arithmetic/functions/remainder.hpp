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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REMAINDER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REMAINDER_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_remainder remainder
 *
 * \par Description
 * The function computes the remainder of dividing a0 by a1.
 * The return value is a0-n*a1, where n is the value a0/a1,
 * rounded to the nearest integer.
 * If the absolute value of a0-n*a1 is 0.5, n is chosen to be even.
 * \par
 * if one prefer: if a1 is zero returns a0, else return
 * a0-divround(a0,a1)*a1
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/remainder.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg drem
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::remainder_(A0,A0)>::type
 *     remainder(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of remainder
 * \param a1 the second parameter of remainder
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
     * \brief Define the tag remainder_ of functor remainder 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct remainder_ : ext::elementwise_<remainder_> { typedef ext::elementwise_<remainder_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remainder_, remainder, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remainder_, drem, 2)
} }

#endif

// modified by jt the 25/12/2010
