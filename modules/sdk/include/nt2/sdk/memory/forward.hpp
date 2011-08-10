//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_FORWARD_HPP_INCLUDED
#define NT2_SDK_MEMORY_FORWARD_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/memory/config.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/forward.hpp>

namespace nt2 { namespace memory
{
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::memory::reallocate;
} }
#endif

