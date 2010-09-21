//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_AT_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_AT_HPP_INCLUDED
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/first.hpp>
#include <nt2/include/functions/second.hpp>
#include <nt2/include/functions/put_first.hpp>

namespace nt2 { namespace functors
{
//   template<std::size_t Idx,class Extension,class Info>
//   struct validate<at_<Idx>,tag::simd_(tag::arithmetic_,Extension),Info>
//   {
//     template<class Sig> struct result;

//     template<class This,class A0>
//     struct result<This(A0)> : boost::mpl::true_ {};

//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//          : boost::mpl::and_ < meta::is_scalar<A1>
//                             , meta::is_integral<A1>
//                             > {};
//   };
//   template<std::size_t Idx,class Extension,class Info>
//   struct call<at_<Idx>,tag::simd_(tag::arithmetic_,Extension),Info>
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0)> : meta::scalar_of<A0> {};
//     template<class This,class A0,class A1>
//     struct result<This(A0, A1)> : meta::scalar_of<A0> {};

//     NT2_FUNCTOR_CALL(2) { return first(put_first(a0, a1)); }

//     NT2_FUNCTOR_CALL_DISPATCH(
//       1,
//       typename nt2::meta::scalar_of<A0>::type,
//       (6, (types8_,types16_,float,int32_,  double,int64_))
//       )

//   public:

//     NT2_FUNCTOR_CALL_EVAL_IF(1,    int64_)
//     {
//       typedef typename meta::scalar_of<A0>::type sint_type;
//       const sint_type tmp =  (sint_type(_mm_cvtsi128_si32(_mm_srli_si128(a0, 8*Idx))))+
// 	(sint_type(_mm_cvtsi128_si32(_mm_srli_si128(a0, 8*Idx+1))) << 32);
//       return tmp;
//     }

//     NT2_FUNCTOR_CALL_EVAL_IF(1,    double)
//     {
//       typedef typename meta::as_integer<A0>::type type;
//       meta::from_bits<double>::type
//       t = { eval(simd::native_cast<type>(a0),int64_()) };
//       return t.value;
//     }
//      NT2_FUNCTOR_CALL_EVAL_IF(1,    int32_)
//     {
//       return _mm_cvtsi128_si32(_mm_srli_si128(a0, 4*Idx));
//     }

//     NT2_FUNCTOR_CALL_EVAL_IF(1,    float)
//     {
//       typedef typename meta::as_integer<A0>::type type;
//       meta::from_bits<float>::type
//       t = { eval(simd::native_cast<type>(a0),int32_()) };
//       return t.value;
//     }
//     NT2_FUNCTOR_CALL_EVAL_IF(1,    types16_)
//     {
//       return _mm_extract_epi16(a0, Idx);
//     }

//     NT2_FUNCTOR_CALL_EVAL_IF(1,    types8_)
//     {
//       int that = (_mm_extract_epi16(a0, Idx >> 1) >> 8*(Idx&1)) & 0xFF;
//       return that ;
//     }
//   };
} }

#endif
