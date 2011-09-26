//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FAST_FREXP_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_ieee
 * \defgroup fast_frexp fast_frexp function
 *
 * \par Description
 * Split a floating entry in signed mantissa m and exponent e
 * \f$a = m\times 2^e\f$, with absolute value of m
 * between one half and one
 * \parThe fast prefix indicates that for speed sake
 * the result may be incorrect for limiting values:
 * inf, -inf nan and zero that deserve special treatment.If you are not sure use \c frexp at the expense
 * of some more machine cycles.
 * \par
 * As demonstrated in the synopsis this function can be called in various ways.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fast_frexp.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::fast_frexp_(A0 const&)
 *                                       >::type
 *   fast_frexp(A0 const& a0);
 *    template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::fast_frexp_(A0 const&,A0&)
 *                                        >::type
 *   fast_frexp(A0 const& a0,A1& a2);
 *    template<class A0,class A1> inline
 *   int fast_frexp(A0 const& a0,A0& a2,A1& a3);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of fast_frexp
 * \param a1 is the second parameter of fast_frexp, if not present, the function return a boost::fusion sequence
 * \param a2 is the third parameter of fast_frexp, if present will contain the mantissa of a0
 * 
 * \return with one parameter the returned result is a fusion sequence of the two results, with two parameters the returned result is the mantissa, with three parameters the returned result is always 0
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag fast_frexp_ of functor fast_frexp 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct fast_frexp_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_frexp_, fast_frexp, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::fast_frexp_, fast_frexp,(A0 const&)(A1&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::fast_frexp_, fast_frexp,(A0 const&)(A1&),2) 
} }

#endif

// modified by jt the 25/12/2010
