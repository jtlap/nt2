//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE4_1_LOOKUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE4_1_LOOKUP_HPP_INCLUDED
#include <nt2/toolbox/swar/function/simd/sse/ssse3/lookup.hpp>
// #include <nt2/sdk/meta/as_real.hpp>
// #include <nt2/sdk/meta/size.hpp>
// #include <nt2/sdk/meta/strip.hpp>
// #include <nt2/sdk/memory/aligned_type.hpp>
// // #include <nt2/include/functions/at.hpp>
// // #include <nt2/include/functions/load.hpp>
// // #include <nt2/include/functions/store.hpp>



// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is arithmetic_
// /////////////////////////////////////////////////////////////////////////////
// // NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
// //                          (A0),
// //                          ((simd_<arithmetic_<A0>,tag::sse_>))
// //                          ((simd_<integer_<A0>,tag::sse_>))
// //                         );

// // namespace nt2 { namespace ext
// // {
// //   template<class Dummy>
// //   struct call<tag::lookup_(tag::simd_<tag::arithmetic_, tag::sse_> ,
// //                            tag::simd_<tag::integer_, tag::sse_> ),
// //               tag::cpu_, Dummy> : callable
// //   {
// //     template<class Sig> struct result;
// //     template<class This,class A0,class A1>
// //     struct result<This(A0,A1)>
// //       : meta::strip<A0>{};//


// //   };
// // } }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type8_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
//                          (A0),
//                          ((simd_<type8_<A0>,tag::sse_>))
//                          ((simd_<ints8_<A0>,tag::sse_>))
//                         );

// namespace nt2 { namespace ext
// {
//   template<class Dummy>
//   struct call<tag::lookup_(tag::simd_<tag::type8_, tag::sse_> ,
//                            tag::simd_<tag::ints8_, tag::sse_> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//

//     NT2_FUNCTOR_CALL(2)
//     {
//       typedef typename meta::scalar_of<A0>::type sA0;
//       NT2_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
//       NT2_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
//       nt2::store<A0>(a0, &tmp[0], 0);

//       for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
//       return nt2::load<A0>(&tmp1[0], 0);
// //       const int32_t N = meta::cardinal_of<A0>::value;
// //       int64_t mask = _mm_movemask_epi8(is_lt(a1, N));
// //       return simd::native_cast<A0>(_mm_blendv_epi8(a0, mask));
//     }
//   };
// } }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type32_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
//                          (A0),
//                          ((simd_<type32_<A0>,tag::sse_>))
//                          ((simd_<ints32_<A0>,tag::sse_>))
//                         );

// namespace nt2 { namespace ext
// {
//   template<class Dummy>
//   struct call<tag::lookup_(tag::simd_<tag::type32_, tag::sse_> ,
//                            tag::simd_<tag::ints32_, tag::sse_> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//

//     NT2_FUNCTOR_CALL(2)
//     {
//       typedef typename meta::scalar_of<A0>::type sA0;
//       NT2_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
//       NT2_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
//       nt2::store<A0>(a0, &tmp[0], 0);

//       for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
//       return nt2::load<A0>(&tmp1[0], 0);
// //       typedef typename meta::as_real<A0>::type real_type;
// //       const int32_t N = meta::cardinal_of<A0>::value;
// //       int32_t mask = _mm_movemask_ps(is_lt(a1, N));
// //       real_type tmp = {simd::native_cast<real_type>(a0)}; 
// //       return simd::native_cast<A0>(_mm_blend_ps(tmp, mask));
//     }
//   };
// } }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type64_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
//                          (A0),
//                          ((simd_<type64_<A0>,tag::sse_>))
//                          ((simd_<ints64_<A0>,tag::sse_>))
//                         );

// namespace nt2 { namespace ext
// {
//   template<class Dummy>
//   struct call<tag::lookup_(tag::simd_<tag::type64_, tag::sse_> ,
//                            tag::simd_<tag::ints64_, tag::sse_> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//

//     NT2_FUNCTOR_CALL(2)
//     {
//       typedef typename meta::scalar_of<A0>::type sA0;
//       NT2_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
//       NT2_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
//       nt2::store<A0>(a0, &tmp[0], 0);

//       for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
//       return nt2::load<A0>(&tmp1[0], 0);
// //       typedef typename meta::as_real<A0>::type real_type;
// //       const int32_t N = meta::cardinal_of<A0>::value;
// //       int32_t mask = _mm_movemask_pd(is_lt(a1, N));
// //       return simd::native_cast<A0>(_mm_blend_pd(simd::native_cast<real_type>(a0), mask));
//     }
//   };
// } }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type16_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
//                          (A0),
//                          ((simd_<type16_<A0>,tag::sse_>))
//                          ((simd_<ints16_<A0>,tag::sse_>))
//                         );

// namespace nt2 { namespace ext
// {
//   template<class Dummy>
//   struct call<tag::lookup_(tag::simd_<tag::type16_, tag::sse_> ,
//                            tag::simd_<tag::ints16_, tag::sse_> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//

//     NT2_FUNCTOR_CALL(2)
//     {
//       const int32_t N = meta::cardinal_of<A0>::value;
//       int32_t mask = _mm_movemask_epi16(is_lt(a1, N));
//       return simd::native_cast<A0>(_mm_blend_epi16(a0, mask));
//     }
//   };
// } }

#endif
// modified by jt the 05/01/2011
