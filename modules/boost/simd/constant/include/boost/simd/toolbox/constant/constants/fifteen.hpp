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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FIFTEEN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FIFTEEN_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_fifteen Fifteen
 *
 * \par Description
 * Constant Fifteen = 5
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fifteen.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::fifteen_(A0)>::type
 *     Fifteen();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Fifteen
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
     * \brief Define the tag Fifteen of functor Fifteen
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER(Fifteen,int,5,0x41700000,0x402e000000000000ll);
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fifteen, Fifteen)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
