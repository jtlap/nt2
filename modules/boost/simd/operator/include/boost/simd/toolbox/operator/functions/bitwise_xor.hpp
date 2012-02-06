//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_BITWISE_XOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_BITWISE_XOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_bitwise_xor bitwise_xor
 *
 * \par Description
 * return the bitwise xor of the two parameters
 * the operands must share the same bit size and
 * the result type is the one of the first operand
 * Infix notation can be used with operator '^',
 * but this will not work in scalar mode if any
 * operand is floating point because of C++ limitations.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_xor.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg b_xor
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitwise_xor_(A0,A0)>::type
 *     bitwise_xor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of bitwise_xor
 * \param a1 the second parameter of bitwise_xor
 * 
 * \return a value of the type of the first parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag bitwise_xor_ of functor bitwise_xor 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct bitwise_xor_ : ext::elementwise_<bitwise_xor_> { typedef ext::elementwise_<bitwise_xor_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_xor_      , bitwise_xor     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_xor_      , b_xor           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::bitwise_xor>
  {
    typedef boost::simd::tag::bitwise_xor_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::bitwise_xor_>
  {
    typedef boost::proto::tag::bitwise_xor type;
  };
} } }

#endif
