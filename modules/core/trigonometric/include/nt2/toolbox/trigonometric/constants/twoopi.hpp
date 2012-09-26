//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_TWOOPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_TWOOPI_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_twoopi Twoopi constant
 *
 * \par Description
 * Constant twoopi : \f$\frac2\pi\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/twoopi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_twoopi_(A0)>::type
 *     twoopi();
 * }
 * \endcode
 *
 *
 * \param T template parameter of twoopi
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Twoopi, double
                                , 0, 0x3f22f983
                                , 0x3fe45f306dc9c883ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Twoopi, Twoopi);
}

#endif
