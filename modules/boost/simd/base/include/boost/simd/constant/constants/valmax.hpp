//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>


#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // cast truncate constants
#endif

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Valmax generic tag

     Represents the Valmax constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Valmax : ext::pure_constant_<Valmax>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Valmax> parent;

      template<class Target, class Dummy=void>
      struct  apply
      {
        // MSVC has some problem parsing this directly as a base class ...
        typedef typename Target::type target_t;
        static const target_t value = ~(typename Target::type
                                        (   typename Target::type(1)
                                          <<  ( sizeof(typename Target::type)
                                              * CHAR_BIT-1
                                              )
                                        )
                                       );

        typedef  meta::int_c < target_t, value> type;
      };
    };

    template<class T, class Dummy>
    struct  Valmax::apply< boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x7F7FFFFF> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x7FEFFFFFFFFFFFFFULL> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint8_<T>,Dummy>
          : meta::int_c<T, 0xFF> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint16_<T>,Dummy>
          : meta::int_c<T, 0xFFFF> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint32_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFUL> {};

    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint64_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFFFFFFFFFULL> {};
  }
  /*!
    Constant Valmax, maximum value of a type.
    @c int8    127, uint8    255,
    @c int16 32767, uint16 65535,
    @c int32 2147483647, uint32 4294967295,
    @c int64 9223372036854775807, uint64 18446744073709551615,@c float \f$\infty\f$, @c double \f$\infty\f$,
    \par
    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Valmax<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Valmax, Valmax)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
