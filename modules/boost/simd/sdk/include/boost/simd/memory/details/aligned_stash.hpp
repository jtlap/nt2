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
#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <cstddef>
#include <cstring>
#include <algorithm>

namespace boost { namespace simd { namespace details
{
  struct aligned_block_header
  {
    void*         pBlockBase;
    std::size_t   userBlockSize;
  };

  BOOST_FORCEINLINE aligned_block_header& get_block_header( void * const ptr )
  {
    return *reinterpret_cast<aligned_block_header* BOOST_DISPATCH_RESTRICT>
    (
      (static_cast<char*>(ptr) - sizeof(aligned_block_header))
    );
  }

  BOOST_FORCEINLINE void* adjust_pointer( void*       const ptr
                                        , std::size_t const size
                                        , std::size_t const alignment
                                        , std::size_t const old    = 0
                                        , std::size_t const offset = 0
                                        )
  {
    if( !ptr ) return reinterpret_cast<void*>(0);

    void* uptr = static_cast<char*>(ptr) + sizeof(aligned_block_header);

    uptr = simd::align_on(uptr,alignment);

    BOOST_ASSERT_MSG( simd::is_aligned( uptr, alignment )
                    , "memory::adjust_pointer can't align memory as requested."
                    );

    if(old)
      std::memmove(uptr, static_cast<char*>(ptr) + offset, std::min(size,old));

    aligned_block_header& header = get_block_header(uptr);

    header.pBlockBase    = ptr;
    header.userBlockSize = size;

    return uptr;
  }
} } }

#endif
