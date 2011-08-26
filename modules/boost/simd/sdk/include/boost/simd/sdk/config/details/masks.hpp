/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/mpl/int.hpp>

#define BOOST_SIMD_DECLARE_MASK(x,y,z) static const int bit = x, function = y, register_id = z

////////////////////////////////////////////////////////////////////////////////
// Here is the registration of the cpuid masks coming from extensions headers. 
////////////////////////////////////////////////////////////////////////////////

namespace boost{ namespace simd{ namespace config{ namespace details{

////////////////////////////////////////////////////////////////////////////////
// Masks for SIMD extensions on x86 processors and variants.
////////////////////////////////////////////////////////////////////////////////	
  
  //Vendor Tag to select the correct mask.
  struct get_vendor_;
  struct intel_;
  struct amd_;

  template<class Tag = void, class Vendor = void>
  struct cpuid_mask;

  //Use for Vendor detection (Force the two template parameter).
  template<>
  struct cpuid_mask<get_vendor_, void>
  {
    BOOST_SIMD_DECLARE_MASK(0,0x00000000,0); //No bit, all registers required.
  };

  template<class Vendor>
  struct cpuid_mask<tag::sse2_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(26,0x00000001,4);
  };

  template<class Vendor>
  struct cpuid_mask<tag::sse3_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(0,0x00000001,3);
  };

  template<class Vendor>
  struct cpuid_mask<tag::ssse3_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(9,0x00000001,3);
  };

  template<class Vendor>
  struct cpuid_mask<tag::sse4a_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(6,0x80000001,3);
  };

  template<class Vendor>
  struct cpuid_mask<tag::sse4_1_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(19,0x00000001,3);
  };

  template<class Vendor>
  struct cpuid_mask<tag::sse4_2_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(20,0x00000001,3);
  };

  // template<class Vendor>
  // struct cpuid_mask<tag::avx_, Vendor>
  // {
  //   BOOST_SIMD_DECLARE_MASK(28,0x00000001,3);
  // };

  // // Intel mask selection 
  // template<>
  // struct cpuid_mask<tag::fma4_, intel_ >::type >
  // {
  //   BOOST_SIMD_DECLARE_MASK(16,0x80000001,3);
  // };

  // // AMD mask selection 
  // template<>
  // struct cpuid_mask<tag::fma4_, amd_ >::type >
  // {
  //   BOOST_SIMD_DECLARE_MASK(12,0x80000001,3);
  // };

  // template<class Vendor>
  // struct cpuid_mask<tag::xop_, Vendor>
  // {
  //   BOOST_SIMD_DECLARE_MASK(11,0x80000001,3);
  // };

} } } }


#endif
