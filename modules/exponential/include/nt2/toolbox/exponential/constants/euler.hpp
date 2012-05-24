//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_EULER_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_EULER_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup expon_constant
 * \defgroup expon_constant_euler Euler
 *
 * \par Description
 * Constant euler : Euler constant.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/euler.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::euler_(A0)>::type
 *     euler();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Euler
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Euler, double
                                , 0, 0x3f13c468
                                , 0x3fe2788cfc6fb619ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Euler, Euler);
}

#endif
