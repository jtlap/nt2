//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_AVX_RDIVIDE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_AVX_RDIVIDE_HPP_INCLUDED
#include <boost/simd/sdk/meta/upgrade.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/strip.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::rdivide_, tag::cpu_,
                          (A0),
                          ((simd_<arithmetic_<A0>,tag::avx_>))
                          ((simd_<arithmetic_<A0>,tag::avx_>))
                         )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT2(that, boost::simd::rdivide);
      return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::rdivide_, tag::cpu_,
                          (A0),
                          ((simd_<real_<A0>,tag::avx_>))
                          ((simd_<real_<A0>,tag::avx_>))
                         )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return a0/a1;
    }
  };
} }
#endif
