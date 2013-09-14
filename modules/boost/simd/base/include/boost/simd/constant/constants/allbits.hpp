//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Allbits generic tag

     Represents the Allbits constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Allbits : ext::pure_constant_<Allbits>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Allbits> parent;

      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c<typename Target::type, -1>
      {};
    };

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_ < apply < boost::dispatch::meta::uint32_<uint32_t>
                                  , Dummy
                                  >::value
                          > {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_ < apply < boost::dispatch::meta::uint64_<uint64_t>
                                  , Dummy
                                  >::value
                          > {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint8_<T>,Dummy>
          : meta::int_c<T, 0xFF> {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint16_<T>,Dummy>
          : meta::int_c<T, 0xFFFFU> {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint32_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFUL> {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint64_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFFFFFFFFFULL> {};

  }
  /*!
    Constant Allbits : all bits set to 1.

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Allbits<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Allbits, Allbits)
} }

#include <boost/simd/constant/common.hpp>

#endif
