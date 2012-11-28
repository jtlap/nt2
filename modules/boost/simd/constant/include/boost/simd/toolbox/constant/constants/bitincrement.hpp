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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_BITINCREMENT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_BITINCREMENT_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_bitincrement Bitincrement
 *
 * \par Description
 * Constant Bitincrement : represents 0x00000001 bitwise casts in the
 * the corresponding type.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bitincrement.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::bitincrement_(A0)>::type
 *     Bitincrement();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Bitincrement
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
     * \brief Define the tag Bitincrement of functor Bitincrement
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/

    struct Bitincrement : ext::constant_<Bitincrement>
    {
      template<class Target, class Dummy=void>
      struct apply : meta::int_c<typename Target::type,1> {};
    };

    template<class T, class Dummy>
    struct  Bitincrement::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<1> {};

    template<class T, class Dummy>
    struct  Bitincrement::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<1> {};
  }


  BOOST_SIMD_CONSTANT_IMPLEMENTATION( boost::simd::tag::Bitincrement, Bitincrement)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
