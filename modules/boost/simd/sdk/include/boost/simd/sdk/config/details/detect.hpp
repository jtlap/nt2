//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_DETECT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_DETECT_HPP_INCLUDED

/*!
 *\file detect.hpp
*/

#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>

namespace boost{ namespace simd{ namespace config{ namespace details{

  inline bool detect(dispatch::tag::cpu_ const& )
  {
    return false;
  }

#ifdef BOOST_SIMD_ARCH_X86
  bool detect(tag::sse2_ const&   );
  bool detect(tag::sse3_ const&   );
  bool detect(tag::ssse3_ const&  );
  bool detect(tag::sse4a_ const&  );
  bool detect(tag::sse4_1_ const& );
  bool detect(tag::sse4_2_ const& );
  bool detect(tag::avx_ const&    );
#endif
  
#ifdef BOOST_SIMD_ARCH_LRB
  bool detect(tag::lrb_ const&);
#endif

#ifdef BOOST_SIMD_ARCH_POWERPC
  bool detect(tag::altivec_ const&);
#endif

} } } }  

#endif
