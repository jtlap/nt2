//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO_180_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO_180_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_pio_180 pio_180 constant
 *
 * \par Description
 * Constant pio_180 : \f$\frac\pi{180}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/pio_180.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_pio_180_(A0)>::type
 *     pio_180();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Pio_180
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Pio_180, double
                                , 0, 0x3c8efa35
                                , 0x3f91df46a2529d3all
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio_180, Pio_180);
}

#endif
