//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_LOAD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/meta/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief load generic tag

      Represents the load function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct load_ : tag::formal_
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

    load semantic is similar to aligned_load semantic except for the fact that
    memory location doesn't need to be aligned.

    @tparam Type  Type of data to load from memory

    @param ptr    Memory location to load data from.
    @param offset Optional memory offset.

    @return A value of type @c Type loaded from target memory block
  **/
  template<typename Type,typename Pointer,typename Offset>
  BOOST_FORCEINLINE Type
  load(Pointer const& ptr,Offset const& offset )
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::load_
                                  ( Pointer const&
                                  , Offset const&
                                  , boost::dispatch::meta::as_<Type> const
                                  )>::type          callee;
    return callee(ptr,offset,boost::dispatch::meta::as_<Type>());
  }

  /// @overload
  template<typename Type,typename Pointer>
  BOOST_FORCEINLINE Type load(Pointer const& ptr)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::load_
                                  ( Pointer const&
                                  , boost::dispatch::meta::as_<Type> const
                                  )>::type          callee;
    return callee(ptr,boost::dispatch::meta::as_<Type>());
  }
} }

#endif
