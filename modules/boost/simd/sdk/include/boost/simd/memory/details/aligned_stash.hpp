//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_ALIGNED_STASH_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_ALIGNED_STASH_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace details
{
  struct aligned_block_header
  {
    std::size_t offset;
    std::size_t allocated_size;
    std::size_t used_size;
  };

  BOOST_FORCEINLINE aligned_block_header& get_block_header( void * BOOST_DISPATCH_RESTRICT const ptr )
  {
    return *(static_cast<aligned_block_header*>(ptr) - 1);
  }
} } }

#if 0
#include <iostream>
namespace boost { namespace simd { namespace details
{
  void debug_aligned_header( void const * ptr )
  {
    std::cout << "pointer = " << ptr << std::endl;
    if(!ptr)
      return;
    aligned_block_header const &h = *(static_cast<aligned_block_header const*>(ptr) - 1);
    std::cout << "offset = " << h.offset << " (" << static_cast<void const*>(static_cast<char const*>(ptr)+h.offset) << ")" << std::endl;
    std::cout << "allocated_size = " << h.allocated_size << std::endl;
    std::cout << "used_size = " << h.used_size << std::endl;
  }
} } }
#endif

#endif
