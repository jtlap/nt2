//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_SQRT_2OPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_SQRT_2OPI_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_sqrt_2opi Sqrt_2opi
 *
 * \par Description
 * Constant sqrt_2opi : \f$\frac{\sqrt2}{\pi}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrt_2opi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_sqrt_2opi_(A0)>::type
 *     sqrt_2opi();
 * }
 * \endcode
 *
 *
 * \param T template parameter of sqrt_2opi
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_2opi, double
                                , 0, 0x3f4c422a
                                , 0x3fe9884533d43651ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Sqrt_2opi, Sqrt_2opi);
}

#endif
