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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_NOTOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_NOTOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_bitwise_notor bitwise_notor
 *
 * \par Description
 * return the bitwise or of the bitwise complement
 * of the first parameter with the second parameter.
 * \par
 * The operands must share the same bit size and
 * the result type is the one of the first operand
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_notor.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg b_notor
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitwise_notor_(A0,A0)>::type
 *     bitwise_notor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of bitwise_notor
 * \param a1 the second parameter of bitwise_notor
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
     * \brief Define the tag bitwise_notor_ of functor bitwise_notor 
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct bitwise_notor_ : ext::elementwise_<bitwise_notor_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_notor_, bitwise_notor, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_notor_, b_notor, 2)
} }

#endif

// modified by jt the 25/12/2010
