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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_BITWISE_OR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_BITWISE_OR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_bitwise_or bitwise_or
 *
 * \par Description
 * return the bitwise or of the two parameters
 * the operands must share the same bit size and
 * the result type is the one of the first operand
 * Infix notation can be used with operator '|',
 * but this will not work in scalar mode if any
 * operand is floating point because of C++ limitations.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_or.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg b_or
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::bitwise_or_(A0,A1)>::type
 *     bitwise_or(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of bitwise_or
 * \param a1 the second parameter of bitwise_or
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
     * \brief Define the tag bitwise_or_ of functor bitwise_or 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct bitwise_or_ : ext::elementwise_<bitwise_or_> { typedef ext::elementwise_<bitwise_or_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_or_      , bitwise_or     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_or_      , b_or           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::bitwise_or>
  {
    typedef boost::simd::tag::bitwise_or_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::bitwise_or_>
  {
    typedef boost::proto::tag::bitwise_or type;
  };
} } }

#endif
