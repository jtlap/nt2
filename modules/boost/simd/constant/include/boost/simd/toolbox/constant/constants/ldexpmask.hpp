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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_LDEXPMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_LDEXPMASK_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_ldexpmask Ldexpmask
 *
 * \par Description
 * Constant Ldexpmask
 * This constant is the mask to extract the exponent
 * bits of a floating point value
 * \par
 * Its value depends of the type of the template parameter
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ldexpmask.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::ldexpmask_(A0)>::type
 *     Ldexpmask();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Ldexpmask
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
     * \brief Define the tag Ldexpmask of functor Ldexpmask
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Ldexpmask : ext::constant_<Ldexpmask>
    {
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c<typename Target::type,0> {};
    };

    template<class T, class Dummy>
    struct  Ldexpmask::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,0x7F800000> {};

    template<class T, class Dummy>
    struct  Ldexpmask::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,0x7FF0000000000000ULL> {};
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Ldexpmask, Ldexpmask)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
