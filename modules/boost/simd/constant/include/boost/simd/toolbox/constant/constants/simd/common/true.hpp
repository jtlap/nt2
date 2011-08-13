//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_TRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_TRUE_HPP_INCLUDED

#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/simd/tags.hpp>

namespace boost { namespace simd { namespace tag
{
  template<class Target, class Dummy>
  struct  True::apply<Target,simd_type,Dummy> 
        : mpl::integral_c<Target,Target(~0ULL)> {};
      
  template<class Dummy>
  struct  True::apply<float,simd_type,Dummy> 
        : meta::float_<0xFFFFFFFFUL> {};

  template<class Dummy>
  struct  True::apply<double,simd_type,Dummy> 
        : meta::double_<0xFFFFFFFFFFFFFFFFULL> {};
} } }

#endif
