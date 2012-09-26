//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_DEGINRAD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_DEGINRAD_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_deginrad Deginrad
 * \par Description
 * Constant Deginrad : radian in degree  multiplier, \f$\frac\pi{180}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/deginrad.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_deginrad_(A0)>::type
 *     Deginrad();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Deginrad
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    // 8.47842766036889956997e-32
    BOOST_SIMD_CONSTANT_REGISTER( Deginrad, double
                                , 0, 0x3c8efa35
                                , 0x3f91df46a2529d39ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Deginrad, Deginrad);

  static const long double long_deginrad = 0.017453292519943295769236907684886l;
}

#endif
