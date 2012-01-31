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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_bits bits
 *
 * \par Description
 * The function return unsigned integer value which has the same bits of the input
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bits.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bits_(A0)>::type
 *     bits(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of bits
 * 
 * \return an unsigned integer
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag bits_ of functor bits 
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct bits_ : ext::elementwise_<bits_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bits_, bits, 1)
} }

#endif

// modified by jt the 25/12/2010
