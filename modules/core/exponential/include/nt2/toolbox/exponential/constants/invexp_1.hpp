//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_INVEXP_1_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_INVEXP_1_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup expon_constant
 * \defgroup expon_constant_invexp_1 invexp_1 (0.36787944117144232159552377016146...)
 *
 * \par Description
 * Constant invexp_1 : \f$e = \exp(-1)\f$ constant.
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/invexp_1.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::invexp_1_(A0)>::type
 *     invexp_1();
 * }
 * \endcode
 *
 *
 * \param T template parameter of invexp_1
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Invexp_1, double
                                , 2, 0x3ebc5ab2
                                , 0x3fd78b56362cef38ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invexp_1, Invexp_1);
}

#endif
