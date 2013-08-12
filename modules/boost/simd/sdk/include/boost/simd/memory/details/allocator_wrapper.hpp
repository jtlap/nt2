//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_ALLOCATOR_WRAPPER_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_ALLOCATOR_WRAPPER_HPP_INCLUDED

namespace boost { namespace simd { namespace details
{
  template<typename Allocator>
  struct allocator_wrapper
  {
    static void setup(Allocator& a, std::size_t alg = 1)
    {
      alloc = &a;
      align = alg;
    }

    static void* allocate(std::size_t sz)
    {
      return alloc->allocate(sz/sizeof(typename Allocator::value_type));
    }

    static void deallocate(void* ptr)
    {
      typedef typename Allocator::pointer type;
      return alloc->deallocate(type(ptr),0);
    }

    static Allocator* alloc;
    static std::size_t align;

    private:
    allocator_wrapper& operator=(allocator_wrapper const&);
  };

  template<typename Allocator>
  std::size_t allocator_wrapper<Allocator>::align = 0;

  template<typename Allocator>
  Allocator* allocator_wrapper<Allocator>::alloc = 0;
} } }

#endif
