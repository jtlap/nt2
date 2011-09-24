//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPARE_EQUAL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>



/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_operator
 * \defgroup compare_equal compare_equal function
 *
 * \par Description
 * return a bool that is the result of the lexicographic
 * test for equality of all elements of the entries
 * I.e. return true if and only if all corresponding entries
 * elements are equal.
 * \par
 * It is probably not what you wish. Have a look to <tt>is_equal</tt>
 * \par
 * Infix notation can be used with operator '=='
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/compare_equal.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg compare_eq
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::compare_equal_(A0,A0)>::type
 *     compare_equal(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of compare_equal
 * \param a1 is the second parameter of compare_equal
 * 
 * \return a value of the common type of the parameters
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
     * \brief Define the tag compare_equal_ of functor compare_equal 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    typedef boost::proto::tag::equal_to compare_equal_;
  }
    
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_equal_, compare_equal , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_equal_, compare_eq    , 2 )
} }

#endif
