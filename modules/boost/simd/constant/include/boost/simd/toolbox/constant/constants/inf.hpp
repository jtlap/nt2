//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INF_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include/valmax.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct Inf 
    { 
      typedef double default_type;
      template<class Target, class Dummy=void> 
      struct apply : Valmax::apply<Target,Dummy> {};  
    };
  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Inf, Inf)
} }

#endif
