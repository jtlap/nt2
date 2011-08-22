//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_FWD_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_FWD_HPP_INCLUDED

#include <boost/config.hpp>

namespace boost { namespace simd
{
  /* MSVC has issues with unions in certain template contexts (bug 684807),
   * so we make it an struct and rely on the fact that the wrapper native type
   * is itself a union with that compiler. */
  template<class T, class X>
  union native;
} }

#endif
