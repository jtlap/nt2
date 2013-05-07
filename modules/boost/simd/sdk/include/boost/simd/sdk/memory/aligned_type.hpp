//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGNED_TYPE_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGNED_TYPE_HPP_INCLUDED

#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/aligned_on.hpp>

////////////////////////////////////////////////////////////////////////////////
// Build an aligned type
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_ALIGNED_TYPE(T) T BOOST_SIMD_ALIGN_ON(BOOST_SIMD_CONFIG_ALIGNMENT)

#endif
