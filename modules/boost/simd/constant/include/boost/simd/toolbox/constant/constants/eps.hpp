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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_EPS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_EPS_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_eps Eps
 *
 * \par Description
 * Constant Eps
 * \arg 1 for integer types
 * \arg \f$ 2^{-52}\f$ for double
 * \arg \f$ 2^{-23}\f$ for float
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/eps.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::eps_(A0)>::type
 *     Eps();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Eps
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
     * \brief Define the tag Eps of functor Eps 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER(Eps,double,1,0X34000000,0x3CB0000000000000ULL);
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Eps, Eps)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
