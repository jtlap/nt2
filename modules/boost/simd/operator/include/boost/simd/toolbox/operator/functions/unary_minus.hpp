//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_UNARY_MINUS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>



/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_operator
 * \defgroup unary_minus unary_minus function
 *
 * \par Description
 * return the elementwise unary minus of the parameter
 * Infix notation can be used with operator '-'
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/unary_minus.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg neg
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::unary_minus_(A0)>::type
 *     unary_minus(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of unary_minus
 * 
 * \return a value of the same type as the parameter
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
     * \brief Define the tag unary_minus_ of functor unary_minus 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    typedef boost::proto::tag::negate unary_minus_;
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_minus_, unary_minus , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_minus_, neg         , 1 )
} }

#endif
