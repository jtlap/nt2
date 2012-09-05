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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MZERO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MZERO_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_mzero Mzero
 *
 * \par Description
 * Constant Mzero = -0
 * This is a special constant as it can be used and considered
 * identical to zero, except that for floating point numbers,
 * there is two different representation of zero with different bit of sign.\par
 * The existence of the sign can be used in special circumstances as
 * choosing between \f$\pm\infty\f$ instead of nan in computing 1/0.
 * \par
 * The sign of zero can be accessed through the is_negative and is_positive predicates.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/mzero.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::mzero_(A0)>::type
 *     Mzero();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Mzero
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
     * \brief Define the tag Mzero of functor Mzero 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Mzero, double, 0
                                , 0x80000000, 0x8000000000000000ULL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mzero, Mzero)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
