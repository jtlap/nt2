//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 20010 - 2011   LRI    UMR 10623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FACT_10_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FACT_10_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_fact_10 Fact_10
 *
 * \par Description
 * Constant Fact_10, 10! = 3628800, the saturated factorial value is
 * min(Valmax<T>(),3628800)
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fact_10.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::fact_10_(A0)>::type
 *     Fact_10();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Fact_10
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
     * \brief Define the tag Fact_10 of functor Fact_10
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER(Fact_10,int,3628800,0x4a5d7c00, 0x414baf8000000000ll)
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_10, Fact_10)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
