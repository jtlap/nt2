/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_VENDOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_VENDOR_HPP_INCLUDED

#include <boost/simd/sdk/config/details/masks/forward.hpp>
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/config/arch.hpp>

#define BOOST_SIMD_DECLARE_MASK(x,y,z) static const int bit = x, function = y, register_id = z
#define BOOST_SIMD_DECLARE_X86_CPUID_CALL(function) int regs_x86[4]; __cpuid(regs_x86, function)
#define BOOST_SIMD_DECLARE_X86_DETECTION_CALL(bit, function, register_id)\
BOOST_SIMD_DECLARE_X86_CPUID_CALL(function); return has_bit_set(regs_x86[register_id-1], bit)

namespace boost{ namespace simd{ namespace config{ namespace details{

  struct get_vendor_;
  struct intel_;
  struct amd_;
  struct ibm_;

  enum { intel, amd, ibm};

////////////////////////////////////////////////////////////////////////////////
//Use for Vendor detection.
////////////////////////////////////////////////////////////////////////////////                                                                     
  template<>
  struct cpuid_mask<get_vendor_, void>
  {
    BOOST_SIMD_DECLARE_MASK(0,0x00000000,0); //No bit, all registers required.
    //Return type is int for the enum vendor
    inline int get_support()
    {
#if !defined(BOOST_SIMD_ARCH_POWERPC)
      BOOST_SIMD_DECLARE_X86_CPUID_CALL(this->function);
      if( str_match(regs_x86, INTEL) ) return intel;
      else if( str_match(regs_x86, AMD) ) return amd;  
#elif defined(BOOST_SIMD_ARCH_POWERPC)
      return ibm;
#endif
    }
  };

} } } }

#endif

