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

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_arithmetic
 * \defgroup abs abs function
 *
 * \par Description
 * The function always returns a value of the same type than the entry.
 * Take care that for signed integers the absolute value of Valmin is Valmin
 * (thus negative!).
 * \par
 * This is a side effect of the 2-complement representation  of integers.
 * To avoid this,  you can use the \c abss saturated functor or convert the
 * input parameter to a larger type before taking the abs value.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/abs.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg modulus
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::abs_(A0)>::type
 *     abs(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of abs
 * 
 * \return a value of the same type as the parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag abs_ of functor abs 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct abs_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abs_, abs, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abs_, modulus, 1)
} }

#endif

// modified by jt the 25/12/2010
