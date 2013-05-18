//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_STORE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief Store generic tag

      Represents the store function in generic contexts like functor creation.

      @par Models:
      @ref FormalHierarchy
    **/
    struct store_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Store a value at an aligned memory location

    Store a given value into an aligned memory location referenced by either
    a pointer or a pointer and an offset. To support SIMD idioms like data
    scattering or non-POD values, both pointer and offset arguments can
    themselves be SIMD register or Fusion Sequences.

    @par Semantic:

    Depending on the type of its arguments, store exhibits different semantics.
    For any @c x of type @c Value, @c ptr of type @c Pointer and @c offset
    of type @c Offset, consider:

    @code
    store(x,ptr,offset);
    @endcode


    If @c x is a SIMD value, this code is equivalent to:
    - If @c offset is a scalar integer:

      @code
      for(int i=0;i<Value::static_size;++i)
        *(ptr+offset+i) = x[i];
      @endcode

    - If @c offset is a SIMD integral register:

      @code
      for(int i=0;i<Value::static_size;++i)
        *(ptr+offset[i]) = x[i];
      @endcode

      In this case, the store operation is equivalent to a scatter operation.

    If @c x and @c ptr are Fusion Sequences of size @c N, this code is
    equivalent to:

    @code
    store(at_c<0>(x),at_c<0>(ptr),offset);
    ...
    store(at_c<N-1>(x),at_c<N-1>(ptr),offset);
    @endcode

    If @c x is a scalar value, this code is equivalent to:

    @code
    *(ptr+offset) = x;
    @endcode

    @par Usage:

    @include memory/store.cpp

    @par Precondition

    If @c Type is a SIMD register type:

    @code
    is_aligned( ptr + offset - Misalignment )
    @endcode

    evaluates to @c true

    @param val    Value to store
    @param ptr    Memory location to store @c val to
    @param offset Optional memory offset.

  **/
  template<typename Value, typename Pointer, typename Offset>
  BOOST_FORCEINLINE void
  store(Value const& val, Pointer const& ptr, Offset const& offset)
  {
    typename boost::dispatch::make_functor<tag::store_, Value>::type callee;
    callee(val, ptr, offset);
  }

  /// @overload
  template<typename Value, typename Pointer>
  BOOST_FORCEINLINE void store(Value const& val, Pointer const& ptr)
  {
    typename boost::dispatch::make_functor<tag::store_, Value>::type callee;
    callee(val, ptr);
  }
} }

#endif
