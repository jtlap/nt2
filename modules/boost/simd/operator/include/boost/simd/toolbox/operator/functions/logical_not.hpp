//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOGICAL_NOT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>



/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_operator
 * \defgroup logical_not logical_not function
 *
 * \par Description
 * return the logical negation of the parameter,
 * i.e. True or False of the entry type according that 
 * the input is zero or non zero
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/logical_not.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg l_not
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::logical_not_(A0)>::type
 *     logical_not(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of logical_not
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
     * \brief Define the tag logical_not_ of functor logical_not 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    typedef boost::proto::tag::logical_not logical_not_;
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_not_ , logical_not  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_not_ , l_not        , 1 )
} }

#endif
