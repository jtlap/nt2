//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_DEALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DEALLOCATE_HPP_INCLUDED

#include <cstddef>
#include <cstdlib>
#include <boost/simd/sdk/memory/forward.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>

namespace boost { namespace simd {  namespace memory
{
  //============================================================================
  /*! 
   * Deallocate a raw buffer of aligned bytes using the current system aligned
   * memory deallocation procedure.
   *
   * \param ptr     Pointer to the memory to free.
   * \param nbytes  Hint on the number of bytes to deallocate. By default, this
   * parameter is equals to 0.
   * \param align   Hint on the alignment boundary used at allocation. By 
   * default, this parameter is equals to the current system SIMD alignment
   * requirement.
   *
   **/ 
  //============================================================================
  inline void deallocate( byte* ptr
                        , std::size_t nbytes
                        , std::size_t align
                        )
  {
    #if defined(BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN)
    //==========================================================================
    // POSIX systems use free
    //==========================================================================
    if(ptr) std::free(ptr);
    #elif (defined _MSC_VER)
    //==========================================================================
    // MSVC systems use _aligned_free
    //==========================================================================
    if(ptr)_aligned_free(ptr);
    #else
    //==========================================================================
    // Other systems do the funky pointer stashing
    //==========================================================================
    if(ptr) std::free( reinterpret_cast<void**>(ptr)[- 1] );
    #endif
  }

  //============================================================================
  /*! 
   * Deallocate a raw buffer of aligned bytes using an allocator.
   *
   * \param alloc   Allocator performing the deallocation
   * \param ptr     Pointer to the memory to free.
   * \param nbytes  Hint on the number of bytes to deallocate. By default, this
   * parameter is equals to 0.
   * \param align   Hint on the alignment boundary used at allocation. By 
   * default, this parameter is equals to the current system SIMD alignment
   * requirement.
   *
   **/ 
  //============================================================================
  template<class Allocator> inline void
  deallocate( Allocator& alloc, byte* ptr
            , std::size_t nbytes
            , std::size_t align 
            )
  {
    typedef typename Allocator::value_type value_type;
    BOOST_STATIC_CONSTANT(std::size_t, size = sizeof(value_type) );


    std::size_t nelems = align_on<size>(nbytes+align+sizeof(void*))/sizeof(size);

    void* p = reinterpret_cast<void**>(ptr)[- 1];
    alloc.deallocate(reinterpret_cast<typename Allocator::pointer>(p),nelems);
  }
} } }

#endif
