//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIX_4_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIX_4_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_pix_4 Pix_4
 *
 * \par Description
 * Constant pix_4 : \f$4\pi\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/pix_4.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_pix_4_(A0)>::type
 *     pix_4();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Pix_4
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Pix_4, double
                                , 12, 0x41490fdb
                                , 0x402921fb54442d18ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix_4, Pix_4);
}

#endif
