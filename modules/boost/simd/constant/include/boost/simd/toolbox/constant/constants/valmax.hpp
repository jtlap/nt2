//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED

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
    struct Valmax 
    { 
      typedef double default_type;
      template<class Target, class Dummy=void> 
      struct  apply 
            : meta::int_c < Target
                          , Target(Target(1) << (sizeof(Target)*CHAR_BIT-1))
                          > 
      {};
    };
    
    template<class Dummy>
    struct  Valmax::apply<float,Dummy> 
          : meta::single_<0x7F7FFFFF> {};

    template<class Dummy>
    struct  Valmax::apply<double,Dummy> 
          : meta::double_<0x7FEFFFFFFFFFFFFFULL> {};

    template<class Dummy>
    struct  Valmax::apply<boost::simd::uint8_t,Dummy> 
          : meta::int_c<boost::simd::uint8_t,0xFF> {};
        
    template<class Dummy>
    struct  Valmax::apply<boost::simd::uint16_t,Dummy> 
          : meta::int_c<boost::simd::uint16_t,0xFFFF> {};
        
    template<class Dummy>
    struct  Valmax::apply<boost::simd::uint32_t,Dummy> 
          : meta::int_c<boost::simd::uint32_t,0xFFFFFFFFUL> {};
        
    template<class Dummy>
    struct  Valmax::apply<boost::simd::uint64_t,Dummy> 
          : meta::int_c<boost::simd::uint64_t,0xFFFFFFFFFFFFFFFFULL> {};

    template<class Dummy>
    struct  Valmax::apply<boost::simd::int8_t,Dummy> 
          : meta::int_c<boost::simd::int8_t,127> {};

    template<class Dummy>
    struct  Valmax::apply<boost::simd::int16_t,Dummy> 
          : meta::int_c<boost::simd::int16_t,32767> {};

    template<class Dummy>
    struct  Valmax::apply<boost::simd::int32_t,Dummy> 
          : meta::int_c<boost::simd::int32_t,2147483647> {};

    template<class Dummy>
    struct  Valmax::apply<boost::simd::int64_t,Dummy> 
          : meta::int_c<boost::simd::int64_t,9223372036854775807ULL> {};
  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Valmax, Valmax)
} }

#endif
