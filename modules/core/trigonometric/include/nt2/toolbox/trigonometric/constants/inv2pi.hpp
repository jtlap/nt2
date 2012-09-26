//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_INV2PI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_INV2PI_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_inv2pi Inv2pi 0.15915494309189533576888376337251
 *
 * \par Description
 * Constant Inv2pi : \f$\frac1\pi\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/inv2pi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_inv2pi_(A0)>::type
 *     Inv2pi();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Inv2pi
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Inv2pi, double
                                  , 0, 0x3e22f983
                                  , 0x3fc45f306dc9c883ll
                                  );
  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Inv2pi, Inv2pi);
}

#endif
