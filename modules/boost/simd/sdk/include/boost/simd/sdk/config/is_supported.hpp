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
// For detecting a new extenion from a new vendor you need to add a vendor case
// and provide the right specialization of cpuid_mask.  
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/config/details/masks.hpp>
#include <boost/simd/sdk/config/details/get_vendor.hpp>
#include <boost/mpl/int.hpp>

namespace boost{ namespace simd{ namespace config{

  template<class Tag>
  bool is_supported()
  {
    switch(details::get_vendor())
    {
    case details::intel : 
      details::cpuid_mask<Tag, details::intel_> mIntel;
      return mIntel.get_support();
    case details::amd :
      details::cpuid_mask<Tag, details::amd_ > mAmd;
      return mAmd.get_support();
    case details::ibm : 
      details::cpuid_mask<Tag, details::ibm_> mIbm;
      return mIbm.get_support();
    default :
      return false;
    }

  }

} } }

#endif
