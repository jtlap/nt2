//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VALMIN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VALMIN_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct Valmin
    { 
      typedef double default_type;
      template<class Target, class Dummy=void> 
      struct apply : meta::int_c<Target,0> {}; 
    };
    
    template<class Dummy>
    struct  Valmin::apply<float,Dummy> 
          : meta::float_<0xFF7FFFFF> {};

    template<class Dummy>
    struct  Valmin::apply<double,Dummy> 
          : meta::double_<0xFFEFFFFFFFFFFFFFULL> {};

    template<class Dummy>
    struct  Valmin::apply<boost::simd::int8_t,Dummy> 
          : meta::int_c<boost::simd::int8_t,-128> {};

    template<class Dummy>
    struct  Valmin::apply<boost::simd::int16_t,Dummy> 
          : meta::int_c<boost::simd::int16_t,-32768> {};

    template<class Dummy>
    struct  Valmin::apply<boost::simd::int32_t,Dummy> 
          : meta::int_c<boost::simd::int32_t,-2147483648UL> {};

    template<class Dummy>
    struct  Valmin::apply<boost::simd::int64_t,Dummy> 
          : meta::int_c<boost::simd::int64_t,-9223372036854775808ULL> {};
  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Valmin, Valmin)
} }

#endif
