//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_FORWARD_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_FORWARD_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/sdk/memory/config.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>

namespace boost { namespace simd {  namespace memory
{
  inline byte* 
  allocate ( std::size_t nbytes
           , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT 
           );
           
  template<class Allocator> inline byte*
  allocate( Allocator& alloc
          , std::size_t nbytes
          , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
          );

  inline void deallocate( byte* ptr
                        , std::size_t nbytes = 0
                        , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT 
                        );

  template<class Allocator> inline void
  deallocate( Allocator& alloc, byte* ptr
            , std::size_t nbytes = 0
            , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT 
            );

  inline byte* reallocate ( byte* ptr
                          , std::size_t nbytes
                          , std::size_t obytes
                          , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT 
                          );
                          
  template<class Allocator> inline byte*
  reallocate( Allocator& a
            ,  byte* ptr
            , std::size_t nbytes
            , std::size_t obytes
            , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT 
            );
} } }

#endif
