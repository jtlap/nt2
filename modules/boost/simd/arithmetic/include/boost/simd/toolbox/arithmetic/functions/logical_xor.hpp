//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_LOGICAL_XOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_arithmetic
 * \defgroup logical_xor logical_xor function
 *
 * \par Description
 * returns the logical xor of  a0 and a1, i.e. returns true 
 * if and only if one of the two parameter is zero andthe other non zero.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/logical_xor.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::logical_xor_(A0,A0)>::type
 *     logical_xor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of logical_xor
 * \param a1 is the second parameter of logical_xor
 * 
 * \return a value of the common type of the parameters
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag logical_xor_ of functor logical_xor 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct logical_xor_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_xor_, logical_xor, 2)
} }

#endif

// modified by jt the 25/12/2010
