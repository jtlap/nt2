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
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ELSE_ZERO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_if_else_zero if_else_zero
 *
 * \par Description
 * If a0 is true returns a1 else returns zero
 * \par
 * The first operand must be a boolean type according to
 * the SIMD architecture compatible to the  other one.
 * the result type is the same as the second parameter one.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/if_else_zero.hpp>
 * \endcode
 *
 * \par Alias
 * \arg ifelsezero
 * \arg ifnot_zero_else
 * \arg ifnotzeroelse
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::if_else_zero_(A0,A1)>::type
 *     if_else_zero(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of if_else_zero
 * \param a1 the second parameter of if_else_zero
 *
 * \return a value of the type of the second parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/



namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag if_else_zero_ of functor if_else_zero
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct if_else_zero_ : ext::elementwise_<if_else_zero_> { typedef ext::elementwise_<if_else_zero_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_zero_, if_else_zero, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_zero_, ifelsezero, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_zero_, ifnot_zero_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_zero_, ifnotzeroelse, 2)
} }

#endif


