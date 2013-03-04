//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_if_zero_else if_zero_else
 *
 * \par Description
 * If a0 is true returns zero else returns a1
 * \par
 * The first operand must be a boolean type according to
 * the SIMD architecture compatible to the  other one.
 * the result type is the same as the second parameter one.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/if_zero_else.hpp>
 * \endcode
 *
 * \par Alias
 * \arg ifzeroelse
 * \arg ifnot_else_zero
 * \arg ifnotelsezero
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::if_zero_else_(A0,A1)>::type
 *     if_zero_else(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of if_zero_else
 * \param a1 the second parameter of if_zero_else
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
     * \brief Define the tag if_zero_else_ of functor if_zero_else
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct if_zero_else_ : ext::elementwise_<if_zero_else_> { typedef ext::elementwise_<if_zero_else_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, if_zero_else,    2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, ifzeroelse,      2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, ifnot_else_zero, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_, ifnotelsezero,   2)
} }

#endif


