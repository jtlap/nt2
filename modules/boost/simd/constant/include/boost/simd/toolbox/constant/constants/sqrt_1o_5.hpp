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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRT_1O_5_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRT_1O_5_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_sqrt_1o_5 Sqrt_1o_5
 *
 * \par Description
 * Constant Sqrt_1o_5 = \f$ \sqrt{\frac15}\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrt_1o_5.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::sqrt_1o_5_(A0)>::type
 *     Sqrt_1o_5();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Sqrt_1o_5
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
     * \brief Define the tag Sqrt_1o_5 of functor Sqrt_1o_5
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_1o_5, double, 0
                                , 0x3ee4f92e, 0x3fdc9f25c5bfedd9ll
                                );
  }


  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrt_1o_5, Sqrt_1o_5)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
