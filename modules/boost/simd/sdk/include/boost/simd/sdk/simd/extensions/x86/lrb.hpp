//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_LRB_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_LRB_HPP_INCLUDED

#if defined(__LRB__)
#  ifndef BOOST_SIMD_HAS_LRB_SUPPORT
#    define BOOST_SIMD_HAS_LRB_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_LRB_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_LRB_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_LRB_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// LRB extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_LRB
#define BOOST_SIMD_LRB_FAMILY
#define BOOST_SIMD_STRING             "LRB"
#define BOOST_SIMD_STRING_LIST        "LRB"
#define BOOST_SIMD_BYTES              64
#define BOOST_SIMD_BITS               512
#define BOOST_SIMD_CARDINALS          (8)(16)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::lrb_)
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::lrb_
#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::lrb_

#include <boost/simd/sdk/simd/extensions/lrb/lrb_prototype_primitives.hpp>
#include <boost/simd/sdk/simd/extensions/lrb/adds2lrb.hpp>
#include <boost/simd/sdk/simd/extensions/meta/lrb.hpp>

#endif
#endif
