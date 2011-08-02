/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_DEALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DEALLOCATE_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/sdk/memory/config.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/simd/sdk/memory/forward.hpp>

namespace boost { namespace simd {  namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Deallocate a raw buffer of bytes using an allocator
  //////////////////////////////////////////////////////////////////////////////
  template<class Allocator> inline void
  deallocate( Allocator& a, byte* ptr, std::size_t nbytes = 0)
  {
    // Allocator element types
    typedef typename Allocator::value_type value_type;

    // Compute alignment values for fixing address
    BOOST_STATIC_CONSTANT(std::size_t, size  = sizeof(value_type)       );
    BOOST_STATIC_CONSTANT(std::size_t, align = BOOST_SIMD_CONFIG_ALIGNMENT     );

    // How many elements are needed ot store proper number of bytes
    std::size_t nelems = align_on<size>(nbytes+align+sizeof(void*))/size;

    void* base = reinterpret_cast<void**>(ptr)[- 1];
    a.deallocate(reinterpret_cast<typename Allocator::pointer>(base),nelems);
  }
} } }



#endif
