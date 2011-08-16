//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_NBDIGITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_NBDIGITS_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct Nbdigits 
    { 
      template<class Target, class Dummy=void> 
      struct  apply : meta::int_c <Target,0> {};  
    };
    
    template<class Dummy>
    struct  Nbdigits::apply<float,Dummy> 
          : meta::int_c<boost::simd::int32_t,24> {};

    template<class Dummy>
    struct  Nbdigits::apply<double,Dummy> 
          : meta::int_c<boost::simd::int64_t,53> {};
  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nbdigits, Nbdigits)
} }

#endif
