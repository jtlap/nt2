//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_MULS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_MULS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/simd/common/muls.hpp>
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is int16_
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::muls_, boost::simd::tag::sse2_,
//                        (A0)(X),
//                        ((simd_<int16_<A0>,X>))((simd_<int16_<A0>,X>))
//                       );
// namespace boost { namespace simd { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<boost::simd::tag::muls_(tag::simd_<tag::int16_, X> ,
// 			 boost::simd::tag::simd_<tag::int16_, X>),
//               boost::simd::boost::simd::tag::sse2_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)> : meta::strip<A0>{};
//     BOOST_SIMD_FUNCTOR_CALL(2)
//     {
//       A0 aa0 = boost::simd::abs(a0);
//       A0 aa1 = boost::simd::abs(a1);
//       A0 mulhi =  simd::native_cast<A0>(_mm_mulhi_epi16(aa0, aa1));
//       A0 mullo =  simd::native_cast<A0>(_mm_mullo_epi16(a0, a1));
//       A0 sign = b_xor(is_ltz(a0), is_ltz(a1));
//       std::cout <<  "mullo "<<  mullo << std::endl;
//       std::cout <<  "mulhi "<<  mulhi << std::endl;
//       return sel(is_eqz(mulhi), mullo, sel(sign, Valmin<A0>(), Valmax<A0>())); 
//     }
//   };
// } } }
  
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is uint16_
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::muls_, boost::simd::tag::sse2_,
//                        (A0)(X),
//                        ((simd_<uint16_<A0>,X>))((simd_<uint16_<A0>,X>))
//                       );
// namespace boost { namespace simd { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<boost::simd::tag::muls_(tag::simd_<tag::uint16_, X> ,
// 			 boost::simd::tag::simd_<tag::uint16_, X>),
//               boost::simd::boost::simd::tag::sse2_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)> : meta::strip<A0>{};
//     BOOST_SIMD_FUNCTOR_CALL(2)
//     {
//       A0 mulhi =  simd::native_cast<A0>(_mm_mulhi_epu16(a0, a1));
//       A0 mullo =  simd::native_cast<A0>(_mm_mullo_epi16(a0, a1));
//       return sel(is_eqz(mulhi), mullo, Valmax<A0>()); 
//     }
//   };
// } } }
#endif
#endif
