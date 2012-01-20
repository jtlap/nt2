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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRTVALMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRTVALMAX_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_sqrtvalmax Sqrtvalmax
 *
 * \par Description
 * Constant Sqrtvalmax : the least non zero positive value of floating point numbers,
 * i.e. 2.225073858507201e-308 for double and  1.1754944e-38 for float
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sqrtvalmax.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::sqrtvalmax_(A0)>::type
 *     Sqrtvalmax();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Sqrtvalmax
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
     * \brief Define the tag Sqrtvalmax of functor Sqrtvalmax 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrtvalmax , double, 1
                                , 0x5f800000, 0x5ff0000000000001ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrtvalmax, Sqrtvalmax)
} }

#endif
