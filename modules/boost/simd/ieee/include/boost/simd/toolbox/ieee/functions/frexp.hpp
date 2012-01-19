//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FREXP_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_frexp frexp
 *
 * \par Description
 * Split a floating entry in signed mantissa m and exponent e
 * \f$a = m\times 2^e\f$, with absolute value of m
 * between one half and one
 * \par
 * As demonstrated in the synopsis this function can be called in various ways.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/frexp.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::frexp_(A0 const&)
 *                                       >::type
 *   frexp(A0 const& a0);
 *    template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::frexp_(A0 const&,A0&)
 *                                        >::type
 *   frexp(A0 const& a0,A1& a2);
 *    template<class A0,class A1> inline
 *   int frexp(A0 const& a0,A0& a2,A1& a3);
 * }
 * \endcode
 *
 * \param a0 the first parameter of frexp
 * \param a1 the second parameter of frexp, if not present, the function return a boost::fusion sequence
 * \param a2 the third parameter of frexp, if present will contain the mantissa of a0
 * 
 * \return with one parameter the returned result is a fusion sequence of the two results, with two parameters the returned result is the mantissa, with three parameters the returned result is always 0
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/
#ifdef frexp
#undef frexp
#endif
namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag frexp_ of functor frexp 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct frexp_ : ext::elementwise_<frexp_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::frexp_, frexp, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::frexp_, frexp,(A0 const&)(A1&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::frexp_, frexp,(A0 const&)(A1&),2) 
} }

#endif

// modified by jt the 25/12/2010
