//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/U.B.P.
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ. Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ABS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ABS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/** \file
 * \brief Defines the absolute value function: abs
 *
 * \par Alias modulus
 *
 * \par Description:
 * the function always returns a value of the same type than the entry.
 * Take care that for signed integers the absolute value of Valmin is Valmin
 * (thus negative!)
 * This is a side effect of the 2-complement representation  of integers.
 * To avoid this,  you can use the "abss" saturated functor or convert the
 * input parameter to a larger type before taking the abs value.
 *
 * \fn template<class A0> A0 abs(const A0& a)
 *
 * \param a0: input param of type A0 a0 
 * 
 * \tparam \c A0 any type
 */

namespace boost { namespace simd { namespace tag
  {
    /*!
     * brief Identification tag for the abs function: tag::abs_
     */
    struct abs_ {};
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abs_, abs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abs_, modulus, 1)
} }
 
#endif

// modified by jt the 25/12/2010
