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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REMQUO_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_remquo remquo
 *
 * \par Description
 * compute the quotient and at least 3 bits of the remainder of the division
 * of a0 by a1. This function correspond to the libc remquo function.
 * \par
 * As demonstrated in the synopsis this function can be called in various ways.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/remquo.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::remquo_(A0 const&,A0 const&)
 *                                       >::type
 *   remquo(A0 const& a0,A0 const& a1 );
 *    template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::remquo_(A0 const&,A1 const&, A0&)
 *                                        >::type
 *   remquo(A0 const& a0,A1const& a1,A0& a2);
 *    template<class A0,class A1> inline
 *   int remquo(A0 const& a0,A1 const& a1,A0& a2,A1& a3);
 * }
 * \endcode
 *
 * \param a0 the first parameter of remquo
 * \param a1 the second parameter of remquo
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag remquo_ of functor remquo 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct remquo_ : ext::elementwise_<remquo_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remquo_, remquo, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::remquo_, remquo,(A0 const&)(A1 const&)(A2&)(A3&),4)
} }

#endif

// modified by jt the 25/12/2010
