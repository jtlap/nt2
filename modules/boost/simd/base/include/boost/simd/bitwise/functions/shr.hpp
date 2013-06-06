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
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SHR_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SHR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_shr shr
 *
 * \par Description
 * The function returns the first entry logically shifted logically right
 * by the absolute value of second entry.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/shr.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::shr_(A0,A0)>::type
 *     shr(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of shr
 * \param a1 the second parameter of shr, must be an integer value
 *
 * \return returns a value of the type of the first parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag shr_ of functor shr
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct shr_ : ext::elementwise_<shr_> { typedef ext::elementwise_<shr_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shr_, shr,  2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shr_, shri, 2)
} }

#endif

// modified by jt the 25/12/2010
