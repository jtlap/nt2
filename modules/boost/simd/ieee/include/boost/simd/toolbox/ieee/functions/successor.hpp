//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SUCCESSOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_ieee
 * \defgroup successor successor function
 *
 * \par Description
 * With one parameter it is equivalent to \c next
 * It is in the type A0, the least A0 elementwise strictly greater than a0
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/successor.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::successor_(A0)>::type
 *     successor(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of successor
 * 
 * \return a value of the same type as the parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag successor_ of functor successor 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct successor_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::successor_, successor, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::successor_, successor, 2)
} }

#endif

// modified by jt the 25/12/2010
