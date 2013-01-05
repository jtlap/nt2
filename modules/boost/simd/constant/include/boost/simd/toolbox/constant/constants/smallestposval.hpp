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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SMALLESTPOSVAL_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_smallestposval Smallestposval
 *
 * \par Description
 * Constant Smallestposval : the least non zero positive value of floating point numbers,
 * i.e. 2.225073858507201e-308 for double and  1.1754944e-38 for float
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/smallestposval.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::smallestposval_(A0)>::type
 *     Sqrtsmallestposval();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Smallestposval
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
     * \brief Define the tag Smallestposval of functor Smallestposval
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Smallestposval , double, 1
                                , 0x00800000, 0x0010000000000000ULL
                                );

  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Smallestposval, Smallestposval)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
