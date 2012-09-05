//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 20011 - 2011   LRI    UMR 11623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FACT_11_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FACT_11_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_fact_11 Fact_11
 *
 * \par Description
 * Constant Fact_11  11! = 39916800, saturated factorial value is
 * min(Valmax<T>(),39916800)
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fact_11.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::fact_11_(A0)>::type
 *     Fact_11();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Fact_11
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
     * \brief Define the tag Fact_11 of functor Fact_11 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER(Fact_11,int,39916800,0x4c184540,0x418308a800000000ll)
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_11, Fact_11)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
