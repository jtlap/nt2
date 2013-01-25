//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_2OSQRTPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_2OSQRTPI_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant__2osqrtpi _2osqrtpi
 *
 * \par Description
 * Constant _2osqrtpi : \f$\frac{2}{\sqrt\pi}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/_2osqrtpi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::__2osqrtpi_(A0)>::type
 *     _2osqrtpi();
 * }
 * \endcode
 *
 *
 * \param T template parameter of _2osqrtpi
 *
 * \return type T value
 *
 **/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( _2osqrtpi, double
                                , 0, 0x3ecc422a
                                , 0x3fd9884533d43651ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_2osqrtpi, _2osqrtpi);//1.1283791670955125738961589031215

}

#endif
