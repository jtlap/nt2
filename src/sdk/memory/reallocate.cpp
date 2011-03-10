/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/sdk/memory/allocate.hpp>
#include <nt2/sdk/memory/deallocate.hpp>
#include <nt2/sdk/memory/reallocate.hpp>

namespace nt2 { namespace memory
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
      result = reinterpret_cast<byte*>(_aligned_realloc(ptr, nbytes, NT2_CONFIG_ALIGNMENT));
      #else
      //////////////////////////////////////////////////////////////////////////
      // Other systems allocate/copy/deallocate
      //////////////////////////////////////////////////////////////////////////
      byte* tmp = reinterpret_cast<byte*>(allocate(nbytes));
      ::memmove(tmp,ptr,obytes);
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
} }
