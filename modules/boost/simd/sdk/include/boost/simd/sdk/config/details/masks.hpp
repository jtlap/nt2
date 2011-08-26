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

#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/mpl/int.hpp>

#define BOOST_SIMD_DECLARE_MASK(x,y,z) static const int bit = x, function = y, register_id = z
#define BOOST_SIMD_DECLARE_CPUID_CALL(function) int regs_x86[4]; __cpuid(regs_x86, function)
#define BOOST_SIMD_DECLARE_X86_DETECTION_CALL(bit, function, register_id)\
BOOST_SIMD_DECLARE_CPUID_CALL(function); return has_bit_set(regs_x86[register_id-1], bit)

////////////////////////////////////////////////////////////////////////////////
// Here is the registration of the cpuid masks coming from extensions headers.
// All SIMD extension detections go down to file.
// When a new SIMD extension needs to be detected at runtime, you can register
// this extension by specializing cpuid_mask on the extension's tag and the 
// vendor. You just need to provide a member function that describes how to 
// detect the extension at runtime and return a boolean.
// You need to follow the same way to add a new vendor detection at runtime. 
////////////////////////////////////////////////////////////////////////////////

namespace boost{ namespace simd{ namespace config{ namespace details{

////////////////////////////////////////////////////////////////////////////////
// Masks for SIMD extensions on x86 processors and variants.
////////////////////////////////////////////////////////////////////////////////	
  
  //Vendor Tag to select the correct mask.
  struct get_vendor_;
  struct intel_;
  struct amd_;
  struct ibm_;

  enum { intel, amd, ibm};

  template<class Tag = void, class Vendor = void>
  struct cpuid_mask;

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse2 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse2_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(26,0x00000001,4);
    bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse2_, ibm_>
  {
    bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse3 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse3_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(0,0x00000001,3);
    bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse3_, ibm_>
  {
    bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for ssse3 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::ssse3_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(9,0x00000001,3);
    bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::ssse3_, ibm_>
  {
    bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse4a detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse4a_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(6,0x80000001,3);
    bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse4a_, ibm_>
  {
    bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse4_1 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse4_1_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(19,0x00000001,3);
    bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    }
  };

  template<>
  struct cpuid_mask<tag::sse4_1_, ibm_>
  {
    bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for sse4_2 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::sse4_2_, Vendor>
  {
    BOOST_SIMD_DECLARE_MASK(20,0x00000001,3);
    bool get_support()
    {
      BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
    } 
 };

  template<>
  struct cpuid_mask<tag::sse4_2_, ibm_>
  {
    bool get_support(){ return false; }
  };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for avx detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  // template<class Vendor>
  // struct cpuid_mask<tag::avx_, Vendor>
  // {
  //   BOOST_SIMD_DECLARE_MASK(28,0x00000001,3);
  //   bool get_support()
  //   {
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   }
  // };

  // template<>
  // struct cpuid_mask<tag::avx_, ibm_>
  // {
  //   bool get_support(){ return false; }
  // };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for fma4 detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  // // Intel mask selection 
  // template<>
  // struct cpuid_mask<tag::fma4_, intel_ >::type >
  // {
  //   BOOST_SIMD_DECLARE_MASK(16,0x80000001,3);
  //   bool get_support()
  //   {
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   }
  // };

  // // AMD mask selection 
  // template<>
  // struct cpuid_mask<tag::fma4_, amd_ >::type >
  // {
  //   BOOST_SIMD_DECLARE_MASK(12,0x80000001,3);
  //   bool get_support()
  //   {
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   } 
  // };

  // template<>
  // struct cpuid_mask<tag::fma4_, ibm_>
  // {
  //   bool get_support(){ return false; }
  // };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for xop detection                                                                                        
////////////////////////////////////////////////////////////////////////////////

  // template<class Vendor>
  // struct cpuid_mask<tag::xop_, Vendor>
  // {
  //   BOOST_SIMD_DECLARE_MASK(11,0x80000001,3);
  //   bool get_support()
  //   {  
  //     BOOST_SIMD_DECLARE_X86_DETECTION_CALL(this->bit, this->function, this->register_id);
  //   }  
  // };

  // template<>
  // struct cpuid_mask<tag::xop_, ibm_>
  // {
  //   bool get_support(){ return false; }
  // };

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for altivec detection                                                                                        
////////////////////////////////////////////////////////////////////////////////
  template<class Vendor>
  struct cpuid_mask<tag::altivec_, Vendor>
  {
    bool get_support(){ return false; }
  };

  template<>
  struct cpuid_mask<tag::altivec_, ibm_>
  {
    bool get_support() { return true; }
  };

////////////////////////////////////////////////////////////////////////////////
//Use for Vendor detection (Force the two template parameter).
////////////////////////////////////////////////////////////////////////////////                                                                     
  template<>
  struct cpuid_mask<get_vendor_, void>
  {
    BOOST_SIMD_DECLARE_MASK(0,0x00000000,0); //No bit, all registers required.
    //Return type is int for the enum vendor
    int get_support()
    {
#if !defined(BOOST_SIMD_ARCH_POWERPC)
      BOOST_SIMD_DECLARE_CPUID_CALL(this->function)
      if( str_match(abcd, INTEL) ) return intel;
      else if( str_match(abcd, AMD) ) return amd;  
#elif defined(BOOST_SIMD_ARCH_POWERPC)
      return ibm;
#endif
    }
  };


} } } }


#endif
