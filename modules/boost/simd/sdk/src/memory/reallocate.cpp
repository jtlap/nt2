/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <cstring>
#include <new>
#include <boost/throw_exception.hpp>
#include <boost/simd/sdk/memory/forward.hpp>

namespace boost { namespace simd { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Reallocate a raw buffer of bytes to a new size
  //////////////////////////////////////////////////////////////////////////////
  byte* reallocate( byte* ptr, std::size_t nbytes, std::size_t obytes)
  {
    byte* result;

    if(obytes < nbytes)
    {
      #if defined(BOOST_MSVC)
      //////////////////////////////////////////////////////////////////////////
      // MSVC systems use _aligned_realloc
      //////////////////////////////////////////////////////////////////////////
      if( !(result = reinterpret_cast<byte*>(_aligned_realloc(ptr, nbytes, BOOST_SIMD_CONFIG_ALIGNMENT)) ) )
      {
        BOOST_THROW_EXCEPTION( std::bad_alloc() );
        result = 0;
      }
      #else
      //////////////////////////////////////////////////////////////////////////
      // Other systems allocate/copy/deallocate
      //////////////////////////////////////////////////////////////////////////
      byte* tmp = allocate(nbytes);
      std::memcpy(tmp,ptr,obytes);
      deallocate(ptr);
      result = tmp;
      #endif
    }
    else
    {
      result = ptr;
    }

    return result;
  }
} } }
