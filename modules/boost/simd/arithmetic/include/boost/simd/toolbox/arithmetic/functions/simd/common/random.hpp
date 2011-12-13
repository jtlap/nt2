//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_RANDOM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_RANDOM_HPP_INCLUDED
//TO DO proper common version

// namespace boost { namespace simd { namespace ext
// {
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::random_, tag::cpu_
//                             , (A0)(X)
//                             , ((simd_<double_<A0>,X>))
//                               ((simd_<double_<A0>,X>))
//                             )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       /* A version of Marsaglia-MultiCarry */
//       static unsigned int I1=1234, I2=5678;
//       I1= 36969*(I1 & 0177777) + (I1>>16);
//       I2= 18000*(I2 & 0177777) + (I2>>16);
//       z = ((I1 << 16)^(I2 & 0177777)) * 2.328306437080797e-10; /* in [0,1) */
//       return a0+(a1-0)*z; 
//     }
//   };
// } } }


#endif
