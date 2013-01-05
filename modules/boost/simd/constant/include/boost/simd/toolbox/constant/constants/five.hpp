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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FIVE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FIVE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_five Five
 *
 * \par Description
 * Constant Five = 5
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/five.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::five_(A0)>::type
 *     Five();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Five
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
     * \brief Define the tag Five of functor Five
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER(Five,int,5,0x40a00000UL,0x4014000000000000ULL);
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Five, Five)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
