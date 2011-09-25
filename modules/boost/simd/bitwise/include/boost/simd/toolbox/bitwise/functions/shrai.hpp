//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SHRAI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SHRAI_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup shrai shrai function
 *
 * \par Description
 * The function returns the first entry arithmetically shifted right
 * by the absolute value of second entry.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/shrai.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::shrai_(A0,A0)>::type
 *     shrai(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of shrai
 * \param a1 is the second parameter of shrai, must be a scalar integer value
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
     * \brief Define the tag shrai_ of functor shrai 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct shrai_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shrai_, shrai, 2)
} }

#endif

// modified by jt the 25/12/2010
