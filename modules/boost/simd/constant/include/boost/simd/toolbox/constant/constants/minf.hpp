//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MINF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MINF_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include/constants/valmin.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct Minf 
    { 
      typedef double default_type;
      template<class Target, class Dummy=void> 
      struct apply : Valmin::apply<Target,Dummy> {};  
    };
    
    template<class Dummy>
    struct  Minf::apply<float,Dummy> 
          : meta::float_<0xFF800000> {};

    template<class Dummy>
    struct  Minf::apply<double,Dummy> 
          : meta::double_<0xFFF0000000000000ULL> {};
  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Minf, Minf)
} }

#endif
