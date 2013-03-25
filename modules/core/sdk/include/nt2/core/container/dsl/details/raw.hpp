//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_RAW_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_RAW_HPP_INCLUDED

#include <nt2/sdk/memory/forward/container.hpp>

namespace nt2 { namespace details
{
  template<typename T>
  BOOST_FORCEINLINE T* raw(T& t)
  {
    return &t;
  }

  template<typename T>
  BOOST_FORCEINLINE T const* raw(T const& t)
  {
    return &t;
  }

  template<typename T, typename S, typename Sema>
  BOOST_FORCEINLINE typename memory::container_ref<T,S,Sema>::pointer
  raw(memory::container_ref<T,S,Sema> const& c)
  {
    return c.raw();
  }

  template<typename T, typename S, typename Sema>
  BOOST_FORCEINLINE typename memory::container_ref<T,S,Sema>::pointer
  raw(memory::container_ref<T,S,Sema>& c)
  {
    return c.raw();
  }

  template<typename T, typename S, typename Sema, bool Own>
  BOOST_FORCEINLINE
  typename memory::container_shared_ref<T,S,Sema,Own>::pointer
  raw(memory::container_shared_ref<T,S,Sema, Own> const& c)
  {
    return c.raw();
  }

  template<typename T, typename S, typename Sema, bool Own>
  BOOST_FORCEINLINE
  typename memory::container_shared_ref<T,S,Sema,Own>::pointer
  raw(memory::container_shared_ref<T,S,Sema, Own>& c)
  {
    return c.raw();
  }

  template<typename T, typename S, typename Sema>
  BOOST_FORCEINLINE typename memory::container<T, S, Sema>::pointer
  raw(memory::container<T, S, Sema>& c)
  {
    return c.raw();
  }

  template<typename T, typename S, typename Sema>
  BOOST_FORCEINLINE typename memory::container<T, S, Sema>::const_pointer
  raw(memory::container<T, S, Sema> const& c)
  {
    return c.raw();
  }
} }

#endif
