//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_POPCNT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_POPCNT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup popcnt popcnt function
 *
 * \par Description
 * The function returns the number of bit sets in each element of the input.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/popcnt.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::popcnt_(A0)>::type
 *     popcnt(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of popcnt
 * 
 * \return always returns an integer value
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag popcnt_ of functor popcnt 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct popcnt_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::popcnt_, popcnt, 1)
} }

#endif

// modified by jt the 25/12/2010
