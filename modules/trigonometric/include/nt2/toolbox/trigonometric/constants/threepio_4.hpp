//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_THREEPIO_4_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_THREEPIO_4_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_threepio_4 Threepio_4 constant
 *
 * \par Description
 * Constant threepio_4 : \f$2\pi\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/threepio_4.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_threepio_4_(A0)>::type
 *     threepio_4();
 * }
 * \endcode
 *
 *
 * \param T template parameter of threepio_4
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    // 8.47842766036889956997e-32
    BOOST_SIMD_CONSTANT_REGISTER( Threepio_4, double
                                , 2, 0x4016cbe4
                                , 0x4002d97c7f3321d2ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Threepio_4, Threepio_4);
}

#endif
