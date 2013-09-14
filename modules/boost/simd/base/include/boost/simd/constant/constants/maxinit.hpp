//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXINIT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXINIT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4146)
#endif


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxinit generic tag

     Represents the Maxinit constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Maxinit : ext::pure_constant_<Maxinit>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Maxinit> parent;

      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename Target::type, 0> {};
    };

    template<class T, class Dummy>
    struct  Maxinit::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0xFF7FFFFFUL> {};

    template<class T, class Dummy>
    struct  Maxinit::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0xFFEFFFFFFFFFFFFFULL> {};

    template<class T, class Dummy>
    struct  Maxinit::apply<boost::dispatch::meta::int8_<T>,Dummy>
          : meta::int_c<T, T(-128)> {};

    template<class T, class Dummy>
    struct  Maxinit::apply<boost::dispatch::meta::int16_<T>,Dummy>
          : meta::int_c<T, T(-32768)> {};

    template<class T, class Dummy>
    struct  Maxinit::apply<boost::dispatch::meta::int32_<T>,Dummy>
    : meta::int_c < T
                  , T(-boost::simd::uint32_t(2147483648UL))
                  >
    {};

    template<class T, class Dummy>
    struct  Maxinit::apply<boost::dispatch::meta::int64_<T>,Dummy>
      : meta::int_c < T
                    , T(-boost::simd::uint64_t(9223372036854775808ULL))
                    >
    {};
  }
  /*!
    Constant Maxinit, the minimum value of a type,  is used to init maxima computations.
    @c int8    -128, uint8  0,
    @c int16 -32768, uint16 0,
    @c int32 -2147483648, uint32 0,
    @c int64 -9223372036854775808, uint64 0,@c float \f$-\infty\f$, @c double \f$-\infty\f$,

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Maxinit<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxinit, Maxinit)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
