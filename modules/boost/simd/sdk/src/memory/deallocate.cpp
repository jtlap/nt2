/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <cstdlib>
#include <boost/simd/sdk/memory/forward.hpp>

namespace boost { namespace simd { namespace memory
{
  void deallocate( byte* ptr, std::size_t )
  {
    #if defined(BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN)
    //////////////////////////////////////////////////////////////////////////////
    // POSIX systems use free
    //////////////////////////////////////////////////////////////////////////////
    if(ptr) std::free(ptr);
    #elif (defined _MSC_VER)
    //////////////////////////////////////////////////////////////////////////////
    // MSVC systems use _aligned_free
    //////////////////////////////////////////////////////////////////////////////
    if(ptr)_aligned_free(ptr);
    #else
    //////////////////////////////////////////////////////////////////////////////
    // Other systems do the funky pointer stashing
    //////////////////////////////////////////////////////////////////////////////
    if(ptr) std::free( reinterpret_cast<void**>(ptr)[- 1] );
    #endif
  }
} } }
