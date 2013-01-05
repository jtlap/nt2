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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SPLITFACTOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SPLITFACTOR_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_splitfactor Splitfactor
 *
 * \par Description
 * Constant Splitfactor is a constant used to split a floating number in two half,
 * in floating point routines such two_add and two_prod to get extra precision.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/splitfactor.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::splitfactor_(A0)>::type
 *     Splitfactor();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Splitfactor
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
     * \brief Define the tag Splitfactor of functor Splitfactor
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Splitfactor, double, 0
                                , 0x46000000, 0x41A0000000000000ULL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Splitfactor, Splitfactor)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
