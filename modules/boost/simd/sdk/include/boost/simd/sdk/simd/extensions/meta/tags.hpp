/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_TAGS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_TAGS_HPP_INCLUDED

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/simd/sdk/config/arch.hpp>

namespace boost { namespace simd { namespace tag
{
////////////////////////////////////////////////////////////////////////////////
// Tag hierarchy for SSE extensions
////////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_HIERARCHY_CLASS(sse_, boost::dispatch::tag::cpu_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse2_, sse_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse3_, sse2_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse4a_, sse3_);
#ifdef BOOST_SIMD_ARCH_AMD
  BOOST_DISPATCH_HIERARCHY_CLASS(ssse3_, sse4a_);
#else
  BOOST_DISPATCH_HIERARCHY_CLASS(ssse3_, sse3_);
#endif
  BOOST_DISPATCH_HIERARCHY_CLASS(sse4_1_, ssse3_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse4_2_, sse4_1_);
  BOOST_DISPATCH_HIERARCHY_CLASS(avx_, sse4_2_);
////////////////////////////////////////////////////////////////////////////////
// Tag hierarchy for Altivec PPC extensions
////////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_HIERARCHY_CLASS(altivec_, boost::dispatch::tag::cpu_);

////////////////////////////////////////////////////////////////////////////////
// Tag hierarchy for no extension
////////////////////////////////////////////////////////////////////////////////  
  template<class N> struct simd_emulation_ : boost::dispatch::tag::cpu_
  {
    typedef boost::dispatch::tag::cpu_ parent;
    typedef simd_emulation_ type;
  };
} } }

#endif
