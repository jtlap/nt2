//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_SQRTPIO_2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_SQRTPIO_2_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_sqrtpio_2 sqrtpio_2
 *
 * \par Description
 * Constant sqrtpio_2 : \f$\frac{\sqrt2}{\pi}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrtpio_2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_sqrtpio_2_(A0)>::type
 *     sqrtpio_2();
 * }
 * \endcode
 *
 *
 * \param T template parameter of sqrtpio_2
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Sqrtpio_2, double
                                , 0, 0x3f62dfc5
                                , 0x3fec5bf891b4ef6bll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Sqrtpio_2, Sqrtpio_2);//0.88622692545275801364908374167057
}

#endif
