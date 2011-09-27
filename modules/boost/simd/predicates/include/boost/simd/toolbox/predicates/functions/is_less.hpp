//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_LESS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_less is_less function
 *
 * \par Description
 * Returns True<A0>() or False<A0>() according a0 is less than a1 or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_less.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg lt
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_less_(A0,A0)>::type
 *     is_less(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of is_less
 * \param a1 is the second parameter of is_less
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
     * \brief Define the tag is_less_ of functor is_less 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_less_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, is_less , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, lt      , 2 )
} }

#endif
