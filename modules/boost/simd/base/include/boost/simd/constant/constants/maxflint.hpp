//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXFLINT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXFLINT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_maxflint Maxflint
 *
 * \par Description
 * Constant Maxflint : the least non zero positive value of floating point numbers,
 * 9007199254740992.0 for double and 16777216.0 for float
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/maxflint.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::maxflint_(A0)>::type
 *     Maxflint();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Maxflint
 *
 * \return type T value
 *
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag Maxflint of functor Maxflint
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxflint , double, 1
                                , 0x4b800000, 0x4340000000000000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxflint, Maxflint)
} }

#include <boost/simd/constant/common.hpp>

#endif
