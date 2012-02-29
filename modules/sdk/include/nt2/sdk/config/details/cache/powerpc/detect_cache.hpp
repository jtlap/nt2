//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONFIG_DETAILS_CACHE_POWERPC_DETECT_CACHE_HPP_INCLUDED
#define NT2_SDK_CONFIG_DETAILS_CACHE_POWERPC_DETECT_CACHE_HPP_INCLUDED

#include <nt2/sdk/config/arch.hpp>

#ifdef NT2_ARCH_POWERPC
#include <boost/simd/sdk/config/details/get_vendor.hpp>
#include <nt2/sdk/error/assert.hpp>

namespace nt2{ namespace config{ namespace details{

  template<class Seq>
  inline void detect_cache(Seq& cache_sizes_, Seq& cache_line_sizes_)
  {
    //Todo: runtime cache detection on ppc
  }

} } }

#endif

#endif
