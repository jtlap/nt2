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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_CTZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_CTZ_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_ctz ctz
 *
 * \par Description
 * The function finds the first bit set (beginning with the least
 * significant bit) in a0, and return the index of that bit.
 * \par
 * Bits are numbered starting at one (the least significant bit).
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/ctz.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::ctz_(A0)>::type
 *     ctz(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ctz
 * 
 * \return always returns an integer value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag ctz_ of functor ctz 
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct ctz_ : ext::elementwise_<ctz_> { typedef ext::elementwise_<ctz_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ctz_, ctz, 1)
} }

#endif

// modified by jt the 25/12/2010
