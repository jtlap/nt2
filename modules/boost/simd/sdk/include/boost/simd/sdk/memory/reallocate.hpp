//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_REALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_REALLOCATE_HPP_INCLUDED

#include <new>
#include <cstring>
#include <cstddef>
#include <boost/throw_exception.hpp>
#include <boost/simd/sdk/memory/forward.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/simd/sdk/memory/allocate.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/deallocate.hpp>

namespace boost { namespace simd {  namespace memory
{
  //============================================================================
  /*! 
   * Reallocated a raw buffer of aligned bytes using the current system aligned
   * memory allocation and deallocation procedure.
   *
   * \param ptr     Pointer to the memory to reallocate.
   * \param nbytes  New number of bytes to allocate
   * \param obytes  Old number of bytes to deallocate
   * \param align   Hint on the alignment boundary used at allocation. By 
   * default, this parameter is equals to the current system SIMD alignment
   * requirement.
   *
   * \return A pointer to a reallocated memory block containing \c nbytes bytes.
   *
   **/ 
  //============================================================================
  inline byte* reallocate ( byte* ptr
                          , std::size_t nbytes
                          , std::size_t obytes
                          , std::size_t align
                          )
  {
    byte* result(ptr);

    if( (obytes < nbytes) || !is_aligned(ptr,align) )
    {
      #if defined(BOOST_MSVC)
      //========================================================================
      // MSVC systems use _aligned_realloc
      //========================================================================
      if( !(  result
           =  reinterpret_cast<byte*>(_aligned_realloc(ptr, nbytes, align)) 
           ) 
        )
      {
        BOOST_THROW_EXCEPTION( std::bad_alloc() );
        result = 0;
      }
      #else
      //========================================================================
      // Other systems allocate/copy/deallocate
      //========================================================================
      byte* tmp = allocate(nbytes, align);
      std::memcpy(tmp,ptr,obytes);
      deallocate(ptr,obytes,align);
      result = tmp;
      #endif
    }

    return result;
  }
  
  //============================================================================
  /*! 
   * Reallocated a raw buffer of aligned bytes using an Allocator.
   *
   * \param alloc   Allocator performing the (de)allocation
   * \param ptr     Pointer to the memory to reallocate.
   * \param nbytes  New number of bytes to allocate
   * \param obytes  Old number of bytes to deallocate
   * \param align   Hint on the alignment boundary used at allocation. By 
   * default, this parameter is equals to the current system SIMD alignment
   * requirement.
   *
   * \return A pointer to a reallocated memory block containing \c nbytes bytes.
   *
   **/ 
  //============================================================================
  template<class Allocator> inline byte*
  reallocate( Allocator& a
            ,  byte* ptr
            , std::size_t nbytes
            , std::size_t obytes
            , std::size_t align
            )
  {
    byte* result(ptr);

    if( obytes < nbytes || !is_aligned(ptr,align) )
    {
      byte* tmp = reinterpret_cast<byte*>(allocate(a,nbytes));
      std::memcpy(tmp,ptr,obytes);
      deallocate(a,ptr,obytes);
      result = tmp;
    }

    return result;
  }
} } }

#endif
