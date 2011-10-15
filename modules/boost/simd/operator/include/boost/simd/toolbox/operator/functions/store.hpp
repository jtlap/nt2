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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_STORE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_store store
 *
 * \par Description
 * Store a data from a0 to the memory zone given by a1 and offset a2
 * and return a0. This is mentally equivalent to:
 * <tt>std::memcpy(reinterpret_cast<A0*>(a1) + a2, &a0, sizeof a0);</tt>
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/store.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::store_(A0,A0)>::type
 *     store(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of store
 * \param a1 the second parameter of store
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

////////////////////////////////////////////////////////////////////////////////
// Store a value in memory functor and function
// Documentation: http://nt2.lri.fr/sdk/memory/functions/store.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/functor/preprocessor/function.hpp>

namespace boost { namespace simd
{
  namespace tag { struct store_ {}; }
    /*!
     * \brief Define the tag store_ of functor store 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::store_,store,3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(tag::store_ , store , 3 )
} }

#endif
