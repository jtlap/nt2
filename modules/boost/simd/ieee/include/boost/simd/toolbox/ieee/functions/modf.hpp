//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_modf modf
 *
 * \par Description
 * Computes the integer part and the fractionnal part of the input
 * \par
 * As demonstrated in the synopsis this function can be called in various ways.
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
 * \param a0 the unique parameter of modf
 *
 * \return with one parameter the returned result is a fusion sequence of the two results, with two parameters the returned result is the intrger part, with three parameters the returned result is always 0
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag modf_ of functor modf
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct modf_ : ext::elementwise_<modf_> { typedef ext::elementwise_<modf_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::modf_, modf, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&)(A1&),2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&),2)

} }

#endif

// modified by jt the 25/12/2010
