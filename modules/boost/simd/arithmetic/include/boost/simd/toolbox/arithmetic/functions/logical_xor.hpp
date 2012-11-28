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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_LOGICAL_XOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_logical_xor logical_xor
 *
 * \par Description
 * returns the logical xor of  a0 and a1, i.e. returns true
 * if and only if one of the two parameter is zero andthe other non zero.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/logical_xor.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::logical_xor_(A0,A0)>::type
 *     logical_xor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of logical_xor
 * \param a1 the second parameter of logical_xor
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a predicate operation. Such operations return bool in scalar mode,
 * but not in SIMD mode.
 * \par
 * The return type in SIMD mode is the common type of the parameters and is
 * a 'signed boolean' type. This means that in this case True has all its bits
 * sets to one. This is to facilitate masking operations. You are invited to
 * consult the rationale.
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag logical_xor_ of functor logical_xor
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct logical_xor_ : ext::elementwise_<logical_xor_> { typedef ext::elementwise_<logical_xor_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_xor_, logical_xor, 2)
} }

#endif

// modified by jt the 25/12/2010
