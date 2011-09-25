//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SHRI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SHRI_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup shri shri function
 *
 * \par Description
 * The function returns the first entry logically shifted right
 * by the absolute value of second entry.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/shri.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::shri_(A0,A0)>::type
 *     shri(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of shri
 * \param a1 is the second parameter of shri, must be a scalar integer value
 * 
 * \return returns a value of the type of the first parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag shri_ of functor shri 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct shri_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shri_, shri, 2)
} }

#endif

// modified by jt the 25/12/2010
