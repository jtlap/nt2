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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_CGOLD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_CGOLD_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_cgold Cgold
 *
 * \par Description
 * Constant Cgold \f$= \frac{1-\sqrt5}{2}\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cgold.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::cgold_(A0)>::type
 *     Cgold();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Cgold
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
     * \brief Define the tag Cgold of functor Cgold
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER(Cgold,double,0,0x3EC3910D,0x3FD8722191A02D61ULL);
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Cgold, Cgold)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
