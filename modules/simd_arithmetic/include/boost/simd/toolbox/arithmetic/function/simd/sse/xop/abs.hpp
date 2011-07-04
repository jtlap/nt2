//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_ABS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_ABS_HPP_INCLUDED
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/include/functions/details/simd/sse/ssse3/abs.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is signed_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<signed_<A0>,tag::xop_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
 //      typedef typename meta::scalar_of<A0>::type sctype;
//       typedef typename simd::native<sctype, tag::sse_ >  svtype;
//       svtype a00 = { _mm256_extractf128_si256(a0, 0)};
//       svtype a01 = { _mm256_extractf128_si256(a0, 1)};
//       A0 that = { _mm256_insertf128_si256(that,boost::simd::abs(a00), 0)};
//       that =  _mm256_insertf128_si256(that,boost::simd::abs(a01), 1);
       BOOST_SIMD_XOP_JOIN128INT1(that, boost::simd::abs);
       return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<unsigned_<A0>,tag::xop_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1){ return a0; }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<real_<A0>,tag::xop_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1){ return b_notand(Mzero<A0>(),a0); }
  };
} } }
#endif
