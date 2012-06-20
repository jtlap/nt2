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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_valmax Valmax
 *
 * \par Description
 * Constant Valmax, maximum value of a type.
 * \arg int8    127, uint8    255,
 * \arg int16 32767, uint16 65535,
 * \arg int32 2147483647, uint32 4294967295,
 * \arg int64 9223372036854775807, uint64 18446744073709551615,\arg float \f$\infty\f$, double \f$\infty\f$,
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/valmax.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::valmax_(A0)>::type
 *     Valmax();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Valmax
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
     * \brief Define the tag Valmax of functor Valmax
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Valmax : ext::constant_<Valmax>
    {
      typedef double default_type;
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename Target::type
                          , typename Target::
                            type( typename Target::type(1)
                                  << (sizeof(typename Target::type)*CHAR_BIT-1)
                                )
                          >
      {};
    };

    template<class T, class Dummy>
    struct  Valmax::apply< boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x7F7FFFFF> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x7FEFFFFFFFFFFFFFULL> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint8_<T>,Dummy>
          : meta::int_c<boost::simd::uint8_t,0xFF> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint16_<T>,Dummy>
          : meta::int_c<boost::simd::uint16_t,0xFFFF> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint32_<T>,Dummy>
          : meta::int_c<boost::simd::uint32_t,0xFFFFFFFFUL> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint64_<T>,Dummy>
          : meta::int_c<boost::simd::uint64_t,0xFFFFFFFFFFFFFFFFULL> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::int8_<T>,Dummy>
          : meta::int_c<boost::simd::int8_t,127> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::int16_<T>,Dummy>
          : meta::int_c<boost::simd::int16_t,32767> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::int32_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,2147483647> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::int64_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,9223372036854775807ULL> {};
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Valmax, Valmax)
} }

#endif
