//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_ieee
 * \defgroup modf modf function
 *
 * \par Description
 * Computes the integer part and the fractionnal part of the input
 * \parAs demonstrated in the synopsis this function can be called in various ways.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/modf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::modf_(A0 const&)
 *                                       >::type
 *   modf(A0 const& a0);
 *    template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::modf_(A0 const&,A0&)
 *                                        >::type
 *   modf(A0 const& a0,A1& a2);
 *    template<class A0> inline
 *   int modf(A0 const& a0,A0& a2,A0& a3);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of modf
 * 
 * \return with one parameter the returned result is a fusion sequence of the two results, with two parameters the returned result is the intrger part, with three parameters the returned result is always 0
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag modf_ of functor modf 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct modf_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::modf_, modf, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&)(A1&),2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&),2) 

} }

#endif

// modified by jt the 25/12/2010
