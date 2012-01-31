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
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_GREATER_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_predicates
 * \defgroup boost_simd_predicates_is_greater is_greater
 *
 * \par Description
 * Returns True<A0>() or False<A0>() according a0 is greater than a1 or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_greater.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg gt
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_greater_(A0,A0)>::type
 *     is_greater(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of is_greater
 * \param a1 the second parameter of is_greater
 * 
 * \return an integer value
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

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag is_greater_ of functor is_greater 
     *        in namespace boost::simd::tag for toolbox boost.simd.predicates
    **/
    struct is_greater_ : ext::elementwise_<is_greater_>{};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, is_greater , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, gt         , 2 )
} }

#endif
