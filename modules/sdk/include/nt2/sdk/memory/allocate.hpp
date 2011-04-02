/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_ALLOCATE_HPP_INCLUDED
#define NT2_SDK_MEMORY_ALLOCATE_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/error/error.hpp>
#include <nt2/sdk/memory/config.hpp>
#include <nt2/sdk/memory/align_on.hpp>

namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Allocate a raw buffer of bytes
  //////////////////////////////////////////////////////////////////////////////
  byte* allocate( std::size_t nbytes );

  //////////////////////////////////////////////////////////////////////////////
  // Allocate a raw buffer of bytes using an allocator
  //////////////////////////////////////////////////////////////////////////////
  template<class Allocator> inline byte*
  allocate( Allocator& a, std::size_t nbytes )
  {
    // Allocator element types
    typedef typename Allocator::value_type value_type;

    // Compute alignment values for fixing address
    BOOST_STATIC_CONSTANT(std::size_t, size  = sizeof(value_type)       );
    BOOST_STATIC_CONSTANT(std::size_t, align = NT2_CONFIG_ALIGNMENT     );
    BOOST_STATIC_CONSTANT(std::size_t, fix   = ~(std::size_t(align-1))  );

    // How many elements are needed ot store proper number of bytes
    std::size_t nelems = align_on<size>(nbytes+align+sizeof(void*))/size;

    // Allocate through a
    void *base     = a.allocate(nelems);

    // Compute stash and position
    std::size_t  ref      = reinterpret_cast<std::size_t>(base)+sizeof(void*);
    std::size_t  stashed  = (ref & fix) + align;
    void        *result   = reinterpret_cast<void*>(stashed);

    // Save the real pointer in the pre-data stash
    reinterpret_cast<void**>(result)[-1] = base;
    return reinterpret_cast<byte*>(result);
  }
} }

#endif
