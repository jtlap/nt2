//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_UNALIGNED_LOAD_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the unaligned_load function
**/

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/meta/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief Unaligned load generic tag

      Represents the unaligned_load function in generic contexts like
      functor creation.

      @par Models:
      @ref ElementwiseHierarchy
    **/
    struct unaligned_load_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Load data from an arbitrary memory location

    Retrieves data from a pointer and an offset using the most efficient
    operations and register types for the chosen destination type.

    @par Semantic

    unaligned_load semantic is similar to load semantic except for the fact that
    memory location doesn't need to be aligned on current architecture preferred
    alignment boundaries.

    @par Usage:

    @include unaligned_load.cpp

    @tparam Type  Type of data to load from memory

    @param ptr    Memory location to load data from.
    @param offset Optional memory offset.

    @return A value of type @c Type loaded from target memory block
  **/
  template<typename Type,typename Pointer,typename Offset>
  BOOST_FORCEINLINE Type
  unaligned_load(Pointer const& ptr,Offset const& offset )
  {
    typename boost::dispatch
                  ::make_functor<tag::unaligned_load_,Pointer>::type callee;

    return callee(ptr,offset,boost::dispatch::meta::as_<Type>());
  }

  /// @overload
  template<typename Type,typename Pointer>
  BOOST_FORCEINLINE Type unaligned_load(Pointer const& ptr)
  {
    typename boost::dispatch
                  ::make_functor<tag::unaligned_load_,Pointer>::type callee;

    return callee(ptr,boost::dispatch::meta::as_<Type>());
  }
} }

#endif
