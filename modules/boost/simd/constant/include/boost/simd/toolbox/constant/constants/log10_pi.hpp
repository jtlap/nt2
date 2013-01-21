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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_LOG10_PI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_LOG10_PI_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_log10_pi Log10_pi
 *
 * \par Description
 * Constant Log10_pi = base ten log of pi used in pispace
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/log10_pi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::log10_pi_(A0)>::type
 *     Log10_Pi();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Log10_Pi
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
     * \brief Define the tag Log10_Pi of functor Log10_Pi
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Log10_pi, double, 3
                                  , 0x3efe8a6e, 0x3fdfd14db31ba3bbll
                                  );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Log10_pi, Log10_pi)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
