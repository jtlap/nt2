//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_TWOTONMB_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_TWOTONMB_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_twotonmb Twotonmb
 *
 * \par Description
 * Constant Twotonmb two to the number of mantissa bits.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/twotonmb.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::twotonmb_(A0)>::type
 *     Twotonmb();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Twotonmb
 * 
 * \return type T value
 *  
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag Twotonmb of functor Twotonmb 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Twotonmb, double, 0
                                , 0x4B000000, 0x4330000000000000ULL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twotonmb, Twotonmb)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
