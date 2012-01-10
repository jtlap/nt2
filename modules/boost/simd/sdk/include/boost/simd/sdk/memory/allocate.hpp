//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALLOCATE_HPP_INCLUDED

#include <new>
#include <cstdlib>
#include <cstddef>
#include <boost/throw_exception.hpp>
#include <boost/simd/sdk/memory/forward.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>

namespace boost { namespace simd {  namespace memory
{
  //============================================================================
  /*! 
   * Allocate a raw buffer of aligned bytes using the current system aligned
   * memory allocation procedure. Dependign on OS and compiler, allocating
   * aligned memory may be done through a system call or by using pointer
   * stashing.
   *
   * \param nbytes Number of bytes to allocate.
   * \param align  Boundary to align memory on. By default, \c align is equals
   * to the current system SIMD alignment requirement.
   *
   * \return A pointer to an aligned memory block of \c nbytes bytes. If the
   * allocation fails, it returns a null pointer and throw a \c std::bad_alloc
   * exception.
   *
   **/ 
  //============================================================================
  inline byte* 
  allocate ( std::size_t nbytes
           , std::size_t align 
           )
  {
    void *result;

    #if defined(BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN)
    //==========================================================================
    // POSIX systems use posix_memalign
    //==========================================================================
    if(posix_memalign(&result, align, nbytes))
    {
      boost::throw_exception( std::bad_alloc() );
      result = 0;
    }
    #elif defined (_MSC_VER)
    //==========================================================================
    // MSVC systems use _aligned_malloc
    //==========================================================================
    if( !(result = _aligned_malloc(nbytes, align) ) )
    {
      boost::throw_exception( std::bad_alloc() );
      result = 0;
    }
    #else
    //==========================================================================
    // Other systems do the funky pointer stashing
    //==========================================================================
    void *base;
    const std::size_t fix = ~(std::size_t(align-1));
    if( !(base = std::malloc(nbytes+align+sizeof(void*))) )
    {
      boost::throw_exception( std::bad_alloc() );
      result = 0;
    }
    else
    {
      std::size_t  ref      = reinterpret_cast<std::size_t>(base)+sizeof(void*);
      result = reinterpret_cast<void*>((ref & fix) + align);
      reinterpret_cast<void**>(result)[-1] = base;
    }
    #endif

    return reinterpret_cast<byte*>(result);
  }

  //==============================================================================
  /*! 
   * Allocate a raw buffer of aligned bytes using an \c Allocator. 
   *
   * \param alloc  The \c Allocator to use for performing allocation
   * \param nbytes Number of bytes to allocate.
   * \param align  Boundary to align memory on. By default, \c align is equals
   * to the current system SIMD alignment requirement.
   *
   * \return A pointer to an aligned memory block of \c nbytes bytes. If the
   * allocation fails, this function may throw a \c std::bad_alloc exception.
   *
   **/ 
  //==============================================================================
  template<class Allocator> inline byte*
  allocate( Allocator& alloc
          , std::size_t nbytes
          , std::size_t align
          )
  {
    typedef typename Allocator::value_type value_type;
    BOOST_STATIC_CONSTANT(std::size_t, size = sizeof(value_type) );
    const std::size_t fix   = ~(std::size_t(align-1));
    
    // How many elements are needed ot store proper number of bytes
    const std::size_t nelems  = align_on<size>(nbytes+align+sizeof(void*))
                              / sizeof(value_type);

    void *base = alloc.allocate(nelems);

    // Compute stash and position
    const std::size_t  ref  = reinterpret_cast<std::size_t>(base)+sizeof(void*);
    void          *result   = reinterpret_cast<void*>((ref & fix) + align);

    // Save the real pointer in the pre-data stash
    reinterpret_cast<void**>(result)[-1] = base;
    return reinterpret_cast<byte*>(result);
  }
} } }

#endif
