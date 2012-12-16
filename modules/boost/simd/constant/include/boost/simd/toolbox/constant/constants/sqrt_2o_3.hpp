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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRT_2O_3_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRT_2O_3_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_sqrt_2o_3 Sqrt_2o_3
 *
 * \par Description
 * Constant Sqrt_2o_3 = \f$ \frac{\sqrt2}3\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrt_2o_3.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::sqrt_2o_3_(A0)>::type
 *     Sqrt_2o_3();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Sqrt_2o_3
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
     * \brief Define the tag Sqrt_2o_3 of functor Sqrt_2o_3
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_2o_3, double, 0
                                , 0x3f5105ec, 0x3fea20bd700c2c3ell
                                );
  }


  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrt_2o_3, Sqrt_2o_3)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
