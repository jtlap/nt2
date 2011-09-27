//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_EQUAL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_equal is_equal function
 *
 * \par Description
 * Returns True<A0>() or False<A0>() according a0 and a1 are equal or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_equal.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg eq
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_equal_(A0,A0)>::type
 *     is_equal(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of is_equal
 * \param a1 is the second parameter of is_equal
 * 
 * \return an integer value
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
     * \brief Define the tag is_equal_ of functor is_equal 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_equal_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_equal_, is_equal , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_equal_, eq      , 2 )
} }

#endif
