/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/sdk/memory/allocate.hpp>

namespace nt2 { namespace memory
{
  byte* allocate( std::size_t nbytes )
  {
    void *result;
    BOOST_STATIC_CONSTANT(std::size_t, align = NT2_CONFIG_ALIGNMENT );

    #if defined(NT2_CONFIG_SUPPORT_POSIX_MEMALIGN)
    //////////////////////////////////////////////////////////////////////////////
    // POSIX systems use posix_memalign
    //////////////////////////////////////////////////////////////////////////////
    if(posix_memalign(&result, align, nbytes))
    {
      NT2_THROW( std::bad_alloc() );
      result = 0;
    }
    #elif defined (_MSC_VER)
    //////////////////////////////////////////////////////////////////////////////
    // MSVC systems use _aligned_malloc
    //////////////////////////////////////////////////////////////////////////////
    if( !(result = _aligned_malloc(nbytes, align) ) )
    {
      NT2_THROW( std::bad_alloc() );
      result = 0;
    }
    #else
    //////////////////////////////////////////////////////////////////////////////
    // Other systems do the funky pointer stashing
    //////////////////////////////////////////////////////////////////////////////
    void *base;
    BOOST_STATIC_CONSTANT(std::size_t, fix = ~(std::size_t(align-1)));
    if( !(base = ::malloc(nbytes+align+sizeof(void*))) )
    {
      NT2_THROW( std::bad_alloc() );
      result = 0;
    }
    else
    {
      std::size_t  ref      = reinterpret_cast<std::size_t>(base)+sizeof(void*);
      std::size_t  stashed  = (ref & fix) + align;
      result = reinterpret_cast<void*>(stashed);
      reinterpret_cast<void**>(result)[-1] = base;
    }
    #endif

    return reinterpret_cast<byte*>(result);
  }
} }
