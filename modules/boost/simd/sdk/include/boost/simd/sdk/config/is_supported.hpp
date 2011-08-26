/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_IS_SUPPORTED_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_IS_SUPPORTED_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Runtime function returning the SIMD extension supported. 
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/config/details/masks.hpp>
#include <boost/mpl/int.hpp>

namespace boost{ namespace simd{ namespace config{

  template<class Tag>
  bool is_supported(void)
  {

#if !defined(BOOST_SIMD_ARCH_POWERPC)

    int regs[4]; 
    // Force tag to instanciate the vendor mask, we only want the vendor.
    details::cpuid_mask<details::get_vendor, details::get_vendor> mvendor;
    if(is_vendor(mvendor, INTEL) == true) 
    {
      details::cpuid_mask<Tag, details::intel> m;
      details::__cpuid(regs,m.function);
      return details::has_bit_set(regs[m.register_id-1], m.bit);
    }
    else if(is_vendor(mvendor, AMD) == true) 
    {
      details::cpuid_mask<Tag, details::amd > m;
      details::__cpuid(regs,m.function);
      return details::has_bit_set(regs[m.register_id], m.bit);
    }
    else return false;

#elif defined(BOOST_SIMD_ARCH_POWERPC) 



#endif

  }

} } }

#endif
