//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_IF_ZERO_ELSE_ONE_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_if_zero_else_one if_zero_else_one
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
 * #include <nt2/include/functions/if_zero_else_one.hpp>
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
 *     meta::call<tag::if_zero_else_one_(A0,A1)>::type
 *     if_zero_else_one(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of if_zero_else_one
 * \param a1 the second parameter of if_zero_else_one
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
     * \brief Define the tag if_zero_else_one_ of functor if_zero_else_one
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct if_zero_else_one_ : ext::elementwise_<if_zero_else_one_> { typedef ext::elementwise_<if_zero_else_one_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_one_, if_zero_else_one,   1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_zero_else_one_, ifzeroelseone,      1)
} }

#endif


