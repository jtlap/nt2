//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
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
  byte* allocate( std::size_t nbytes );
  void deallocate( byte* ptr, std::size_t nbytes = 0);
  byte* reallocate( byte* ptr, std::size_t nbytes, std::size_t obytes);
} } }
#endif

