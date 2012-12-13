//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_DELETER_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DELETER_HPP_INCLUDED

#include <boost/simd/sdk/memory/deallocate.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>

namespace boost { namespace simd { namespace memory
{
  template<class T, std::size_t Align = BOOST_SIMD_CONFIG_ALIGNMENT, class Allocator = void>
  struct deleter
       : Allocator
  {
    deleter() {}
    deleter(Allocator const& x) : Allocator(x) {}

    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x)
    {
      boost::simd::memory::deallocate( static_cast<Allocator&>(*this), reinterpret_cast<byte*>(x), 0u, Align );
    }
  };

  template<class T, std::size_t Align>
  struct deleter<T, Align>
  {
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const
    {
      boost::simd::memory::deallocate( reinterpret_cast<byte*>(x), 0u, Align );
    }
  };
} } }

#endif
