//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_DETAILS_CHECK_PTR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_DETAILS_CHECK_PTR_HPP_INCLUDED

#include <boost/simd/memory/is_aligned.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

#define BOOST_SIMD_DETAILS_CHECK_PTR(Pointer, Alignment)                       \
BOOST_ASSERT_MSG( boost::simd::is_aligned(Pointer,Alignment)                   \
                , "Unaligned memory location. You tried to access a "          \
                  "memory location which is not aligned properly with "        \
                  "respect to current architecture SIMD alignment boundaries." \
                )                                                              \
/**/

#endif
