//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED

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
    struct Allbits 
    { 
      typedef double default_type;
      template<class Target, class Dummy=void> 
      struct  apply 
            : meta::int_c<Target, -1>
      {};
    };
    
    template<class Dummy>
    struct  Allbits::apply<float,Dummy>
          : meta::single_<apply<uint32_t,Dummy>::value> {};
          
    template<class Dummy>
    struct  Allbits::apply<double,Dummy>
          : meta::double_<apply<uint64_t,Dummy>::value> {};

    template<class Dummy>
    struct  Allbits::apply<boost::simd::uint8_t,Dummy> 
          : meta::int_c<boost::simd::uint8_t,0xFF> {};
        
    template<class Dummy>
    struct  Allbits::apply<boost::simd::uint16_t,Dummy> 
          : meta::int_c<boost::simd::uint16_t,0xFFFFU> {};
        
    template<class Dummy>
    struct  Allbits::apply<boost::simd::uint32_t,Dummy> 
          : meta::int_c<boost::simd::uint32_t,0xFFFFFFFFUL> {};
        
    template<class Dummy>
    struct  Allbits::apply<boost::simd::uint64_t,Dummy> 
          : meta::int_c<boost::simd::uint64_t,0xFFFFFFFFFFFFFFFFULL> {};

  }
  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Allbits, Allbits)
} }

#endif
