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

#include <boost/simd/sdk/memory/config.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace memory
{
  byte*
  allocate ( std::size_t nbytes
           , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
           );

  template<class Allocator>
  typename boost::dispatch::meta::enable_if_type< typename Allocator::pointer, byte* >::type
  allocate( Allocator& alloc
          , std::size_t nbytes
          , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
          );

  void
  deallocate( byte* ptr
            , std::size_t nbytes = 0
            , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
            );

  template<class Allocator>
  typename boost::dispatch::meta::enable_if_type< typename Allocator::pointer >::type
  deallocate( Allocator& alloc, byte* ptr
            , std::size_t nbytes = 0
            , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
            );

  byte*
  reallocate( byte* ptr
            , std::size_t nbytes
            , std::size_t obytes
            , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
            );

  template<class Allocator>
  typename boost::dispatch::meta::enable_if_type< typename Allocator::pointer, byte* >::type
  reallocate( Allocator& a
            ,  byte* ptr
            , std::size_t nbytes
            , std::size_t obytes
            , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
            );
} } }

#endif
