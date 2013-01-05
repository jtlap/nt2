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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_ONEO_8_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_ONEO_8_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_oneo_8 Oneo_8
 *
 * \par Description
 * Constant Oneo_8 = 1/8
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/oneo_8.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::oneo_8_(A0)>::type
 *     Oneo_8();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Oneo_8
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
     * \brief Define the tag Oneo_8 of functor Oneo_8
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_8, int, 0
                                 , 0x3e000000, 0x3fc0000000000000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneo_8, Oneo_8)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif

