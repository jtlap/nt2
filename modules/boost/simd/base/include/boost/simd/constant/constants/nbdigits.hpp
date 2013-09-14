//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_NBDIGITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_NBDIGITS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Nbdigits generic tag

     Represents the Nbdigits constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Nbdigits : ext::pure_constant_<Nbdigits>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Nbdigits> parent;

      template<class Target, class Dummy=void>
      struct  apply : meta::int_c <typename Target::type,0> {};
    };

    template<class T, class Dummy>
    struct  Nbdigits::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,24> {};

    template<class T, class Dummy>
    struct  Nbdigits::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,53> {};
  }
  /*!
    Constant Nbdigits, The number of mantissa bits of a floating point number,
    i.e. 53 for double and 24 for float.

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Nbdigits<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nbdigits, Nbdigits)
} }

#include <boost/simd/constant/common.hpp>

#endif
