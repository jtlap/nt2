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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_TWOTO31_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_TWOTO31_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_twoto31 Twoto31
 *
 * \par Description
 * Constant Twoto31 = \f$2^{-10}\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/twoto31.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::twoto31_(A0)>::type
 *     Twoto31();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Twoto31
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
     * \brief Define the tag Twoto31 of functor Twoto31
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Twoto31, double, (1 << 31)
                                , 0x4f000000, 0x41e0000000000000LL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Twoto31, Twoto31)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
