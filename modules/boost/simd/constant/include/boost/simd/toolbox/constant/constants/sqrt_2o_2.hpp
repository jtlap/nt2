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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRT_2O_2_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRT_2O_2_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_sqrt_2o_2 Sqrt_2o_2
 *
 * \par Description
 * Constant Sqrt_2o_2 = \f$ \frac{\sqrt2}2\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrt_2o_2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::sqrt_2o_2_(A0)>::type
 *     Sqrt_2o_2();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Sqrt_2o_2
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
     * \brief Define the tag Sqrt_2o_2 of functor Sqrt_2o_2
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_2o_2, double, 0
                                , 0x3F3504F3, 0x3FE6A09E667F3BCDULL
                                );
  }


  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrt_2o_2, Sqrt_2o_2)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
