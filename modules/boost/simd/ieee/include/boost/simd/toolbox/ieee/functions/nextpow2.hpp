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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEXTPOW2_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEXTPOW2_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_nextpow2 nextpow2
 *
 * \par Description
 * Returns the least n such that abs(a0) is less or equal to \f$2^n\f$
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/nextpow2.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::nextpow2_(A0)>::type
 *     nextpow2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of nextpow2
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag nextpow2_ of functor nextpow2 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct nextpow2_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::nextpow2_, nextpow2, 1)
} }

#endif

// modified by jt the 25/12/2010
