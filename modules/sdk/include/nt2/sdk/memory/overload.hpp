/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_OVERLOAD_HPP_INCLUDED
#define NT2_SDK_MEMORY_OVERLOAD_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/memory/allocate.hpp>
#include <nt2/sdk/memory/deallocate.hpp>

////////////////////////////////////////////////////////////////////////////////
// Macro for operator new/new[] overload with aligned allocation
////////////////////////////////////////////////////////////////////////////////
#define NT2_MEMORY_OVERLOAD_NEW_DELETE(A)                           \
void* operator new(std::size_t s)                                   \
{                                                                   \
  return nt2::memory::allocate(s);                                  \
}                                                                   \
void* operator new[](std::size_t s)                                 \
{                                                                   \
  return nt2::memory::allocate(s);                                  \
}                                                                   \
void operator delete(void *p)                                       \
{                                                                   \
  nt2::memory::deallocate(reinterpret_cast<nt2::memory::byte*>(p)); \
}                                                                   \
void operator delete[](void *p)                                     \
{                                                                   \
  nt2::memory::deallocate(reinterpret_cast<nt2::memory::byte*>(p)); \
}                                                                   \
/**/

#endif
