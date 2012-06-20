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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_NBMANTISSABITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_NBMANTISSABITS_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_nbmantissabits Nbmantissabits
 *
 * \par Description
 * Constant Nbmantissabits, The number of mantissa bits of a floating point number,
 * i.e. 53 for double and 24 for float.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/nbmantissabits.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::nbmantissabits_(A0)>::type
 *     Nbmantissabits();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Nbmantissabits
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
     * \brief Define the tag Nbmantissabits of functor Nbmantissabits
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Nbmantissabits : ext::constant_<Nbmantissabits>
    {
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c < typename Target::type
                                  , sizeof(typename Target::type)*CHAR_BIT
                                  >
      {};
    };

    template<class T, class Dummy>
    struct  Nbmantissabits::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,23> {};

    template<class T, class Dummy>
    struct  Nbmantissabits::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,52> {};
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nbmantissabits, Nbmantissabits)
} }

#endif
