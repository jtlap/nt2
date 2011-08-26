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
  bool is_supported()
  {

#if !defined(BOOST_SIMD_ARCH_POWERPC)

    int regs[4]; 
    switch(details::get_vendor())
    {
    case details::intel : 
      details::cpuid_mask<Tag, details::intel_> mIntel;
      details::__cpuid(regs,mIntel.function);
      return details::has_bit_set(regs[mIntel.register_id-1], mIntel.bit);
    case details::amd :
      details::cpuid_mask<Tag, details::amd_ > mAmd;
      details::__cpuid(regs,mAmd.function);
      return details::has_bit_set(regs[mAmd.register_id-1], mAmd.bit);
    case details::none :
      return false;
    default :
      return false;
    }

#elif defined(BOOST_SIMD_ARCH_POWERPC) 


#endif

  }

} } }

#endif
