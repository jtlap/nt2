//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_HMSB_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_HMSB_HPP_INCLUDED
#include <boost/simd/include/functions/bits.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hmsb_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
      
    typedef boost::simd::uint32_t result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::scalar_of<A0>::type stype; 
      typedef typename dispatch::meta::as_integer<stype,signed>::type sitype;
      
 //      std::cout << "icitte" << std::endl; 
//       const stype mask = Signmask<stype>(); 
//       const result_type N = boost::simd::meta::cardinal_of<A0>::value; 
      result_type z; //=boost::simd::uint32_t( boost::simd::bits(a0[0])&mask) >> N;
//       for(result_type i = 1; i< N; ++i)
//       {
// 	std::cout << a0[i] << std::endl;
// 	std::cout << b_and(a0[i], mask) << std::endl;
// 	std::cout << shri(b_and(mask, a0[i]), N-i) << std::endl; 
//         z |=shri(b_and(mask, a0[i])), N-i);
//       }
      return z;
    }
  };
} } }
#endif
