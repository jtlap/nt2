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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRTSMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SQRTSMALLESTPOSVAL_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_sqrtsmallestposval Sqrtsmallestposval
 *
 * \par Description
 * Constant Sqrtmallestposval : the square root of the least non zero positive value of floating point numbers,
 * i.e.1.491668146240041e-154 for double and 1.0842022e-19 for float
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
 *     meta::call<tag::sqrtsmallestposval_(A0)>::type
 *     Sqrtsmallestposval();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Sqrtsmallestposval
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
     * \brief Define the tag Sqrtsmallestposval of functor Sqrtsmallestposval 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrtsmallestposval , double, 1
                                , 0x20000000, 0x2000000000000000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrtsmallestposval, Sqrtsmallestposval)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
