//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_ARM_DETECT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_ARM_DETECT_HPP_INCLUDED

#include <boost/simd/sdk/config/arch/arm.hpp>

#if defined(BOOST_SIMD_ARCH_ARM)
#include <boost/simd/sdk/config/details/detector/linux_auxv.hpp>

#if defined(BOOST_SIMD_OS_LINUX)
#include <asm/hwcap.h>
#endif

namespace boost { namespace simd { namespace config { namespace details
{
  inline bool detect(tag::neon_ const&)
  {
#if defined(BOOST_SIMD_OS_LINUX)
    return config::linux_::hwcap() & HWCAP_NEON;
#else
    return false;
#endif
  }

} } } }

#endif

#endif
