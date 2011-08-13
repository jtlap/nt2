//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_GENERIC_SIGNMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_GENERIC_SIGNMASK_HPP_INCLUDED

#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>

namespace boost { namespace simd { namespace tag
{
  template<class Dummy>
  struct  Signmask::apply<float,Dummy> 
        : meta::float_<0x80000000> {};

  template<class Dummy>
  struct  Signmask::apply<double,Dummy> 
        : meta::double_<0x8000000000000000ULL> {};
        
  template<class Dummy>
  struct  Signmask::apply<boost::simd::int8_t,Dummy> 
        : mpl::integral_c<boost::simd::int8_t,0x80> {};

  template<class Dummy>
  struct  Signmask::apply<boost::simd::int16_t,Dummy> 
        : mpl::integral_c<boost::simd::int16_t,0x8000> {};

  template<class Dummy>
  struct  Signmask::apply<boost::simd::int32_t,Dummy> 
        : mpl::integral_c<boost::simd::int32_t,0x80000000> {};

  template<class Dummy>
  struct  Signmask::apply<boost::simd::int64_t,Dummy> 
        : mpl::integral_c<boost::simd::int64_t,0x8000000000000000LL> {};
} } }

#endif
