//==============================================================================
//         Copyleft 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyleft 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SHIFT_LEFT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>



/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_operator
 * \defgroup shift_left shift_left function
 *
 * \par Description
 * return left shift of the first operand by the second
 * that must be of integer type and of the same number
 * of elements as the first parameter
 * Infix notation can be used with operator '<<'
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/shift_left.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg shl
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::shift_left_(A0,A1)>::type
 *     shift_left(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of shift_left
 * \param a1 is the second parameter of shift_left, must be integer
 * 
 * \return a value of the type of the first parameter
 *  
 * \internal end_functor \endinternal
**/
 
 
namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag shift_left_ of functor shift_left 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    typedef boost::proto::tag::shift_left shift_left_;
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shift_left_             , shift_left     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shift_left_             , shl            , 2 )
} }

#endif
