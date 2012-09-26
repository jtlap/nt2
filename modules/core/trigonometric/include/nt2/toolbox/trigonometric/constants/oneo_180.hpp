//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_ONEO_180_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_ONEO_180_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_oneo_180 oneo_180
 *
 * \par Description
 * Constant Oneo_180 : \f$\frac1{180}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/oneo_180.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_oneo_180_(A0)>::type
 *     Oneo_180();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Oneo_180
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_180, double
                                , 0, 0x3bb60b61
                                , 0x3f76c16c16c16c17ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Oneo_180, Oneo_180);
}

#endif
