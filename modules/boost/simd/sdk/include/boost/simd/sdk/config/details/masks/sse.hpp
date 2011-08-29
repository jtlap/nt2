/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_SSE_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_SSE_HPP_INCLUDED

#include <boost/simd/sdk/config/details/masks/forward.hpp>
#include <boost/simd/sdk/config/details/masks/vendor.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>

namespace boost{ namespace simd{ namespace config{ namespace details{

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse2 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse2_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(26,0x00000001,4);
    inline bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse2_, ibm_>
  {
    inline bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse3 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse3_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(0,0x00000001,3);
    inline bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse3_, ibm_>
  {
    inline bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for ssse3 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::ssse3_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(9,0x00000001,3);
    inline bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::ssse3_, ibm_>
  {
    inline bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse4a detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse4a_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(6,0x80000001,3);
    inline bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse4a_, ibm_>
  {
    inline bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse4_1 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse4_1_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(19,0x00000001,3);
    inline bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse4_1_, ibm_>
  {
    inline bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse4_2 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse4_2_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(20,0x00000001,3);
    inline bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    } 
 };

  template<>
  struct cpuid_mask<tag::sse4_2_, ibm_>
  {
    inline bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for avx detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  // template<class Vendor>
  // struct cpuid_mask<tag::avx_, Vendor>
  // {
  //   BOOST_SIMD_DECLARE_MASK(28,0x00000001,3);
  //   inline bool get_support()
  //   {
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   }
  // };

  // template<>
  // struct cpuid_mask<tag::avx_, ibm_>
  // {
  //   inline bool get_support(){ return false; }
  // };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for fma4 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  // // Intel mask selection 
  // template<>
  // struct cpuid_mask<tag::fma4_, intel_ >::type >
  // {
  //   BOOST_SIMD_DECLARE_MASK(16,0x80000001,3);
  //   inline bool get_support()
  //   {
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   }
  // };

  // // AMD mask selection 
  // template<>
  // struct cpuid_mask<tag::fma4_, amd_ >::type >
  // {
  //   BOOST_SIMD_DECLARE_MASK(12,0x80000001,3);
  //   inline bool get_support()
  //   {
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   } 
  // };

  // template<>
  // struct cpuid_mask<tag::fma4_, ibm_>
  // {
  //   inline bool get_support(){ return false; }
  // };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for xop detection                                                                                        
////////////////////////////////////////////////////////////////////////////////

  // template<class Vendor>
  // struct cpuid_mask<tag::xop_, Vendor>
  // {
  //   BOOST_SIMD_DECLARE_MASK(11,0x80000001,3);
  //   inline bool get_support()
  //   {  
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   }  
  // };

  // template<>
  // struct cpuid_mask<tag::xop_, ibm_>
  // {
  //   inline bool get_support(){ return false; }
  // };

} } } }

#endif

