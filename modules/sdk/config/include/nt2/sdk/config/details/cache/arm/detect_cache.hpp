//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONFIG_DETAILS_CACHE_ARM_DETECT_CACHE_HPP_INCLUDED
#define NT2_SDK_CONFIG_DETAILS_CACHE_ARM_DETECT_CACHE_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>

#ifdef BOOST_SIMD_ARCH_ARM

namespace nt2 { namespace config { namespace details
{
  template<class Seq>
  inline void detect_cache(Seq& cache_sizes_, Seq& cache_line_sizes_)
  {
    // dummy detect_cache
    // by default all is zero
  }
} } }

#endif

#endif
