//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_UNALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief Unaligned store generic tag

      Represents the unaligned_store_ function in generic contexts
      like functor creation.

      @par Models:
      @ref FormalHierarchy
    **/
    struct unaligned_store_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Store a value at an arbitrary memory location

    Store a given value into a random memory location referenced by either
    a pointer or a pointer and an offset. To support SIMD idioms like data
    scattering or non-POD values, both pointer and offset arguments can
    themselves be SIMD register or Fusion Sequences.

    @par Semantic:

    unaligned_store semantic is similar to store semantic except for the fact
    that memory location doesn't need to be aligned on current architecture
    preferred alignment boundaries.

    @param val    Value to stream
    @param ptr    Memory location to stream @c val to
    @param offset Optional memory offset.
  **/
  template<typename Value, typename Pointer, typename Offset>
  BOOST_FORCEINLINE void
  unaligned_store(Value const& val, Pointer const& ptr, Offset const& offset)
  {
    typename boost::dispatch
                  ::make_functor<tag::unaligned_store_,Value>::type callee;
    callee(val, ptr, offset);
  }

  /// @overload
  template<typename Value, typename Pointer>
  BOOST_FORCEINLINE void
  unaligned_store(Value const& val, Pointer const& ptr)
  {
    typename boost::dispatch
                  ::make_functor<tag::unaligned_store_,Value>::type callee;
    callee(val, ptr);
  }
} }

#endif
