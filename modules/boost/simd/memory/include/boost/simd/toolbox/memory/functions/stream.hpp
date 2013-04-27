//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_STREAM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_STREAM_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the stream function
**/

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief Stream generic tag

      Represents the stream function in generic contexts like functor creation.

      @par Models:
      @ref ElementwiseHierarchy
    **/
    struct stream_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Stream a value in memory

    Store a given value into an arbitrary memory location referenced by either
    a pointer or a pointer and an offset without polluting the caches.

    @par Semantic:

    stream semantic is similar to store semantic except for the fact that no
    cache pollution occurs on architecture that support such memory operations.
    On other architecture, stream is simply an alias for store.

    @param val    Value to stream
    @param ptr    Memory location to stream @c val to
    @param offset Optional memory offset.
  **/
  template<typename Value, typename Pointer, typename Offset>
  BOOST_FORCEINLINE void
  stream(Value const& val, Pointer const& ptr, Offset const& offset)
  {
    typename boost::dispatch::make_functor<tag::stream_, Value>::type callee;
    callee(val, ptr, offset);
  }

  /// @overload
  template<typename Value, typename Pointer>
  BOOST_FORCEINLINE void stream(Value const& val, Pointer const& ptr)
  {
    typename boost::dispatch::make_functor<tag::stream_, Value>::type callee;
    callee(val, ptr);
  }
} }

#endif
