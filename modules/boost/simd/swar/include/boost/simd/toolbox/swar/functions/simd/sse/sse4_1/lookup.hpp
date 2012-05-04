//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_LOOKUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT
#include <boost/simd/toolbox/swar/functions/simd/sse/ssse3/lookup.hpp>
// #include <boost/dispatch/meta/as_floating.hpp>
// #include <boost/simd/sdk/meta/size.hpp>
// #include <boost/dispatch/meta/strip.hpp>
// #include <boost/simd/sdk/memory/aligned_type.hpp>
// // #include <boost/simd/include/functions/simd/at.hpp>
// // #include <boost/simd/include/functions/simd/load.hpp>
// // #include <boost/simd/include/functions/simd/store.hpp>
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is arithmetic_
// /////////////////////////////////////////////////////////////////////////////
// // BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::lookup_, boost::simd::tag::sse4_1_,
// //                          (A0),
// //                          ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
// //                          ((simd_<integer_<A0>,boost::simd::tag::sse_>))
// //                         );
// // namespace boost { namespace ext
// // {
// //   template<class Dummy>
// //   struct call<boost::simd::tag::lookup_(tag::simd_<tag::arithmetic_, tag::sse_> ,
// //                            boost::simd::tag::simd_<tag::integer_, tag::sse_> ),
// //               boost::simd::boost::simd::tag::sse4_1_, Dummy> : callable
// //   {
// //     template<class Sig> struct result;
// //     template<class This,class A0,class A1>
// //     struct result<This(A0,A1)>
// //       : meta::strip<A0>{};//
// //   };
// // } } }
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type8_
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::lookup_, boost::simd::tag::sse4_1_,
//                          (A0),
//                          ((simd_<type8_<A0>,boost::simd::tag::sse_>))
//                          ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
//                         );
// namespace boost { namespace ext
// {
//   template<class Dummy>
//   struct call<boost::simd::tag::lookup_(tag::simd_<tag::type8_, tag::sse_> ,
//                            boost::simd::tag::simd_<tag::ints8_, tag::sse_> ),
//               boost::simd::boost::simd::tag::sse4_1_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//
//     BOOST_SIMD_FUNCTOR_CALL(2)
//     {
//       typedef typename meta::scalar_of<A0>::type sA0;
//       BOOST_SIMD_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
//       BOOST_SIMD_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
//       boost::simd::store<A0>(a0, &tmp[0], 0);
//       for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
//       return boost::simd::load<A0>(&tmp1[0], 0);
// //       const int32_t N = meta::cardinal_of<A0>::value;
// //       int64_t mask = _mm_movemask_epi8(is_lt(a1, N));
// //       return simd::bitwise_cast<A0>(_mm_blendv_epi8(a0, mask));
//     }
//   };
// } } }
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type32_
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::lookup_, boost::simd::tag::sse4_1_,
//                          (A0),
//                          ((simd_<type32_<A0>,boost::simd::tag::sse_>))
//                          ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
//                         );
// namespace boost { namespace ext
// {
//   template<class Dummy>
//   struct call<boost::simd::tag::lookup_(tag::simd_<tag::type32_, tag::sse_> ,
//                            boost::simd::tag::simd_<tag::ints32_, tag::sse_> ),
//               boost::simd::boost::simd::tag::sse4_1_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//
//     BOOST_SIMD_FUNCTOR_CALL(2)
//     {
//       typedef typename meta::scalar_of<A0>::type sA0;
//       BOOST_SIMD_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
//       BOOST_SIMD_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
//       boost::simd::store<A0>(a0, &tmp[0], 0);
//       for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
//       return boost::simd::load<A0>(&tmp1[0], 0);
// //       typedef typename dispatch::meta::as_floating<A0>::type real_type;
// //       const int32_t N = meta::cardinal_of<A0>::value;
// //       int32_t mask = _mm_movemask_ps(is_lt(a1, N));
// //       real_type tmp = {simd::bitwise_cast<real_type>(a0)}; 
// //       return simd::bitwise_cast<A0>(_mm_blend_ps(tmp, mask));
//     }
//   };
// } } }
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type64_
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::lookup_, boost::simd::tag::sse4_1_,
//                          (A0),
//                          ((simd_<type64_<A0>,boost::simd::tag::sse_>))
//                          ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
//                         );
// namespace boost { namespace ext
// {
//   template<class Dummy>
//   struct call<boost::simd::tag::lookup_(tag::simd_<tag::type64_, tag::sse_> ,
//                            boost::simd::tag::simd_<tag::ints64_, tag::sse_> ),
//               boost::simd::boost::simd::tag::sse4_1_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//
//     BOOST_SIMD_FUNCTOR_CALL(2)
//     {
//       typedef typename meta::scalar_of<A0>::type sA0;
//       BOOST_SIMD_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
//       BOOST_SIMD_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
//       boost::simd::store<A0>(a0, &tmp[0], 0);
//       for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
//       return boost::simd::load<A0>(&tmp1[0], 0);
// //       typedef typename dispatch::meta::as_floating<A0>::type real_type;
// //       const int32_t N = meta::cardinal_of<A0>::value;
// //       int32_t mask = _mm_movemask_pd(is_lt(a1, N));
// //       return simd::bitwise_cast<A0>(_mm_blend_pd(simd::bitwise_cast<real_type>(a0), mask));
//     }
//   };
// } } }
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is type16_
// /////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::lookup_, boost::simd::tag::sse4_1_,
//                          (A0),
//                          ((simd_<type16_<A0>,boost::simd::tag::sse_>))
//                          ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
//                         );
// namespace boost { namespace ext
// {
//   template<class Dummy>
//   struct call<boost::simd::tag::lookup_(tag::simd_<tag::type16_, tag::sse_> ,
//                            boost::simd::tag::simd_<tag::ints16_, tag::sse_> ),
//               boost::simd::boost::simd::tag::sse4_1_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)>
//       : meta::strip<A0>{};//
//     BOOST_SIMD_FUNCTOR_CALL(2)
//     {
//       const int32_t N = meta::cardinal_of<A0>::value;
//       int32_t mask = _mm_movemask_epi16(is_lt(a1, N));
//       return simd::bitwise_cast<A0>(_mm_blend_epi16(a0, mask));
//     }
//   };
// } } }
#endif
#endif
